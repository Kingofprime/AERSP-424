#include "FlightSIm.h"
#include <cmath>

class Gyroscope : public FlightSim, public Vector, public Matrix
{
public:
	Gyroscope() {}

	Vector Dym(vector Ang_velocities) 
	{
		double phi;
		double theta;
		double psi;

		Matrix R(cos(theta) * cos(psi), cos(theta) * sin(psi), -sin(theta),-cos(phi) * sin(psi) + sin(phi) * sin(theta) * cos(psi), cos(phi) * cos(psi) + sin(phi) * sin(theta) * sin(psi), sin(phi) * cos(theta),sin(phi) * sin(psi) + cos(phi) * sin(theta) * cos(psi), -sin(phi) * cos(psi) + cos(phi) * sin(theta) * sin(psi), cos(phi) * cos(theta));

		Vector Omega_gyro;
		
		while (t <= T) 
		{
			Vector error(1, 1, 1);
			Vector bias(.2, .52, 5);

			FlightSim::dynamics(u);
			FlightSim::integration();
			FlightSim::Angles();

			Omega_gyro += (R * Ang_velocities) + bias + error;

		}

		return Omega_gyro
	}
}
main()
{
// simulation parameters
	double T = 3, dt = 0.001, t = 0;

	// system parameters
	const double m = 1.5, Ix = 0.05, Iy = 0.05, Iz = 0.07, g = 9.81;

	// states
	state_t x = {0,0,-1,0,0,0,0,0,0,0,0,0};
	
	// state derivatives
	state_t xd = {0,0,0,0,0,0,0,0,0,0,0,0};

	// input
	input_t u = { 0,0,-m * g,1,0,0 };

	// params
	params_t p = { m, Ix, Iy, Iz, g, dt };

	FlightSim fs ( x );
	fs.set_params ( p );

	// simulation
	while ( t <= T )
	{
		fs.dynamics ( u );
		fs.integration ();
		fs.Angles ();
		t += dt;
	}
a= Gyroscope Dym();
cout << a << endl;  
