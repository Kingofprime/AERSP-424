#include <iostream>
#include <random>
#include <cmath>

using namespace std;

//worked with Nigam

#define PI 3.14159265358979323846
#define NUM_STATES 12
#define NUM_INPUTS 6
#define NUM_PARAMS 6

struct state_t {
	double x, y, z, u, v, w, phi, theta, psi, p, q, r;
};
struct control_t {
	double Fx, Fy, Fz, Mx, My, Mz;
};
struct params_t {
	double m, Ix, Iy, Iz, g, dt;
};

class FlightSim
{
public:
	FlightSim();
	~FlightSim();
	void set_init_state(const state_t s);
	void set_params(const params_t s);
	void dynamics(double Fx, double Fy, double Fz, double Mx, double My, double Mz);
	void integration();
	void constrainAngles();
	void print_state();
	static void constrainAngle(double& angle);
	virtual void set_actuators(double val1, double val2, double val3, double val4) = 0;

protected:
	state_t s, s_dot;
	params_t p;
};

FlightSim::FlightSim(){}
FlightSim::~FlightSim(){}
void FlightSim::set_init_state(const state_t s)
{
	//this->s.x = s.x;
	//this->s.y = s.y;
	//this->s.z = s.z;
	//this->s.u = s.u;
	//this->s.v = s.v;
	//this->s.w = s.w;
	//this->s.phi = s.phi;
	//this->s.theta = s.theta;
	//this->s.psi = s.psi;
	//this->s.p = s.p;
	//this->s.q = s.q;
	//this->s.r = s.r;
	const double* ptr1 = &(s.x);
	double* ptr2 = &(this->s.x);
	for (unsigned int i = 0; i < NUM_STATES; i++)
	{
		*ptr2++ = *ptr1++;
	}
}
void FlightSim::set_params(const params_t p)
{
	const double* ptr1 = &(p.m);
	double* ptr2 = &(this->p.m);
	for (unsigned int i = 0; i < NUM_PARAMS; i++)
	{
		*ptr2++ = *ptr1++;
	}
}
void FlightSim::dynamics(double Fx, double Fy, double Fz, double Mx, double My, double Mz)
{
	double s_phi = sin(this->s.phi);
	double c_phi = cos(this->s.phi);
	double s_theta = sin(this->s.theta);
	double c_theta = cos(this->s.theta);
	double s_psi = sin(this->s.psi);
	double c_psi = cos(this->s.psi);
	this->s_dot.x = this->s.u * c_theta * c_psi + this->s.v * (s_phi * s_theta * c_psi - c_phi * s_psi) + this->s.w * (c_phi * s_theta * c_psi + s_phi * s_psi);
	this->s_dot.y = this->s.u * c_theta * s_psi + this->s.v * (s_phi * s_theta * s_psi + c_phi * c_psi) + this->s.w * (c_phi * s_theta * s_psi - s_phi * c_psi);
	this->s_dot.z = this->s.u * -s_theta + this->s.v * s_phi * c_theta + this->s.w * c_phi * c_theta;
	this->s_dot.u = this->s.r * this->s.v - this->s.q * this->s.w - this->p.g * s_theta + Fx / this->p.m;
	this->s_dot.v = -this->s.r * this->s.u + this->s.p * this->s.w + this->p.g * s_phi * c_theta + Fy / this->p.m;
	this->s_dot.w = this->s.q * this->s.u - this->s.p * this->s.v + this->p.g * c_phi * c_theta + Fz / this->p.m;
	this->s_dot.phi = this->s.p + (this->s.q * s_phi + this->s.r * c_phi) * s_theta/ c_theta;
	this->s_dot.theta = this->s.q * c_phi - this->s.r * s_phi;
	this->s_dot.psi = (this->s.q * s_phi + this->s.r * c_phi) / c_theta;
	this->s_dot.p = (this->p.Iy - this->p.Iz) * this->s.q * this->s.r / this->p.Ix+ Mx / this->p.Ix;
	this->s_dot.q = (this->p.Iz - this->p.Ix) * this->s.p * this->s.r / this->p.Iy+ My / this->p.Iy;
	this->s_dot.r = (this->p.Ix - this->p.Iy) * this->s.p * this->s.q / this->p.Iz+ Mz / this->p.Iz;
}
void FlightSim::integration()
{
	double* ptr = &(this->s.x);
	double* ptr_dot = &(this->s_dot.x);
	for (unsigned int i = 0; i < NUM_STATES; i++)
	{
		*ptr += *ptr_dot * this->p.dt;
		ptr++;
		ptr_dot++;
	}
}
void FlightSim::constrainAngles()
{
	this->constrainAngle(this->s.phi);
	this->constrainAngle(this->s.theta);
	this->constrainAngle(this->s.psi);
}
void FlightSim::print_state()
{
	double* ptr = &(this->s.x);
	for (unsigned int i = 0; i < NUM_STATES; i++)
	{
		std::cout << *ptr++ << ", ";
	}
	std::cout << std::endl;
}
void FlightSim::constrainAngle(double& angle)
{
	angle -= 2 * PI * std::floor((angle + PI) / (2 * PI));
}

class Multirotor : public FlightSim
{
private:
	double k_t = .001, k_tau = .0001, l = .1;

	double Om1 = 10;
	double Om2 = 20;
	double Om3 = 30;
	double Om4 = 40;

	double Fx = 0;
	double Fy = 0;
	double Fz = 0;
	double Mx = 0;
	double My = 0;
	double Mz = 0;

public:
	void set_actuators(double Om1, double Om2, double Om3, double Om4) override
	{
		this->Fx = 0;
		this->Fy = 0;
		this->Fz = (k_t * pow(Om1, 2)) + (k_t * pow(Om2, 2)) + (k_t * pow(Om3, 2)) + (k_t * pow(Om4, 2));
		this->Mx = ((-l * k_t) * pow(Om1, 2)) + ((l * k_t) * pow(Om2, 2)) + ((l * k_t) * pow(Om3, 2)) - ((l * k_t) * pow(Om4, 2));
		this->My = ((l * k_t) * pow(Om1, 2)) + ((l * k_t) * pow(Om2, 2)) - ((l * k_t) * pow(Om3, 2)) - ((l * k_t) * pow(Om4, 2));
		this->Mz = (k_tau * pow(Om1, 2)) - (k_tau * pow(Om2, 2)) + (k_tau * pow(Om3, 2)) - (k_tau * pow(Om4, 2));
	}
	void update_Multirotor()
	{

		this->set_actuators(Om1, Om2, Om3, Om4);
		//this->dynamics(Fx, Fy, Fz, Mx, My, Mz);
		this->integration();
		this->constrainAngles();
	}

	void print_info()
	{
		std::cout << "Multirotors position (x, y, z): (" << this->s.x << ", " << this->s.y << ", " << this->s.z << ")" << std::endl;
	}

};

class Airplane : public FlightSim
{
private:
	double x_t = 1, x_a = 0, x_e = 0, x_r = 0;
	double y_t = 0, y_a = 0, y_e = 0, y_r = 0.5;
	double z_t = -0.5, z_a = 0, z_e = -0.1, z_r = 0;
	double l_t = 0, l_a = 1.0, l_e = 0, l_r = 0.1;
	double m_t = 0.01, m_a = 0, m_e = 1.0, m_r = 0;
	double n_t = 0, n_a = 0.01, n_e = 0, n_r = 1.0;

	double dt = 0.25;
	double da = 0.5;
	double de = 0.69;
	double dr = 0.75;

	double Fx = 0;
	double Fy = 0;
	double Fz = 0;
	double Mx = 0;
	double My = 0;
	double Mz = 0;

public:

	void set_actuators(double dt, double da, double de, double dr) override
	{
		this->Fx = (x_t * dt) + (x_a * da) + (x_e * de) + (x_r * dr);
		this->Fy = (y_t * dt) + (y_a * da) + (y_e * de) + (y_r * dr);
		this->Fz = (z_t * dt) + (z_a * da) + (z_e * de) + (z_r * dr);
		this->Mx = (l_t * dt) + (l_a * da) + (l_e * de) + (l_r * dr);
		this->My = (m_t * dt) + (m_a * da) + (m_e * de) + (m_r * dr);
		this->Mz = (n_t * dt) + (n_a * da) + (n_e * de) + (n_r * dr);
	}

	void update_Airplane()
	{
		this->set_actuators(dt, da, de, dr);
		//this->dynamics(Fx, Fy, Fz, Mx, My, Mz);
		this->integration();
		this->constrainAngles();
	}

	void print_info()
	{
		std::cout << "Airplane position (x, y, z): (" << this->s.x << ", " << this->s.y << ", " << this->s.z << ")" << std::endl;
	}
};

class ATC
{
public:
	static void ADSB(Multirotor& vehicle1, Airplane& vehicle2) {
		vehicle1.print_info();
		vehicle2.print_info();
	}
};

int main()
{
	// Simulation parameters
	double T = 3, dt = 0.1, t = 0;
	control_t cntrl = { 0,0,-1.5 * 9.81,1,0,0 };
	// system parameters
	const double m = 1.5, Ix = 0.05, Iy = 0.05, Iz = 0.07, g = 9.81;
	// states
	state_t x = { 0,0,-1,0,0,0,0,0,0,0,0,0 };
	// state derivatives
	state_t xd = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	
	// params
	params_t p = { m, Ix, Iy, Iz, g, dt };

	Multirotor MR;
	Airplane AP;

	while (t <= T)
	{
		MR.update_Multirotor();
		AP.update_Airplane();
		ATC::ADSB(MR, AP);


		t += dt;
	}

	return 0;
}