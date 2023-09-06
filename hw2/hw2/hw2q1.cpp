#include <random>
#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <string>
#include <string>
#include <vector>

using namespace std;

// when i use the MVS to run this, the output doesn't randomise until i restart the project, I didn't realised this because i was using an online complier to do this hw

#define gridsize 5
#define noobots 3
#define nowall 2
#define nolakes 4
#define nowoods 4
#define noroads gridsize*gridsize - nowall - nolakes - nowoods

#define World std::array<std::array<std::string,gridsize>, gridsize >
#define Cost std::map<unsigned int, std::map<std::string, unsigned int> >
#define Grid std::pair<unsigned int, unsigned int>

unsigned int random_number_in_an_interval(unsigned int min, unsigned int max)
{
    return min + (rand() % (unsigned int)(max - min + 1));
}
void print_world(std::array<std::array<std::string, 5>, 5 > w)
{
    std::cout << "------------------------------------" << std::endl;
    for (unsigned int i = 0; i < w.size(); i++)
    {
        std::cout << "| ";
        for (unsigned int j = 0; j < w[0].size(); j++)
        {
            std::cout << w[i][j];
            std::cout << " | ";
        }
        std::cout << std::endl << "------------------------------------" << std::endl;
    }
}
// this is one approach to map the terrain and the robot type to a cost value.
// you can also use a container instead of this function.
unsigned int get_cost_from_robot_and_terrain(std::string terrain, unsigned int robot_type)
{
    if (terrain == "wall")
    {
        // robot types do not matter if it's a wall.
        return 999;
    }
    else if (terrain == "road")
    {
        if (robot_type == 1) return 1; // need to return an appropriate number.
        else if (robot_type == 2) return 5; // need to return an appropriate number.
        else if (robot_type == 3) return 5; // need to return an appropriate number.
    }
    else if (terrain == "lake")
    {
        if (robot_type == 1) return 10; // need to return an appropriate number.
        else if (robot_type == 2) return 1; // need to return an appropriate number.
        else if (robot_type == 3) return 10; // need to return an appropriate number.
    }
    else if (terrain == "wood")
    {
        if (robot_type == 1) return 10; // need to return an appropriate number.
        else if (robot_type == 2) return 10; // need to return an appropriate number.
        else if (robot_type == 3) return 1; // need to return an appropriate number.
    }
    else if (terrain == "INIT")
    {
        if (robot_type == 1) return 0; // need to return an appropriate number.
        else if (robot_type == 2) return 0; // need to return an appropriate number.
        else if (robot_type == 3) return 0; // need to return an appropriate number.
    }
    else if (terrain == "GOAL")
    {
        if (robot_type == 1) return 0; // need to return an appropriate number.
        else if (robot_type == 2) return 0; // need to return an appropriate number.
        else if (robot_type == 3) return 0; // need to return an appropriate number.
    }

}
void create_world(std::array<std::array<std::string, 5>, 5 >& world)
{
    unsigned int count_wall = 0, count_wood = 0, count_lake = 0, count_road = 0;
    for (unsigned int i = 0; i < world.size(); i++)
    {
        for (unsigned int j = 0; j < world[0].size(); j++)
        {
            unsigned int n = 0;
            if (i != 0 || j != 0)
            {
                if (i != 4 || j != 4)
                {
                    n = random_number_in_an_interval(0, 3);
                    if (n == 0 && count_road < 5 * 5 - 2 - 4 - 4 - 1 - 1)
                    {
                        count_road++;
                        world[i][j] = "road";
                    }
                    else if (n == 1 && count_wall < 2)
                    {
                        // we don't want the wall to block our initial and goal locations.
                        // this may not necessary if your randomization is better than the approach in this example.
                            if ((i == 0 && j == 1) || (i == 1 && j == 0) || (i == 3 && j == 4
                                ) || (i == 4 && j == 3))
                            {
                                j--;
                                continue;
                            }
                        count_wall++;
                        world[i][j] = "wall";
                    }
                    else if (n == 2 && count_wood < 4)
                    {
                        count_wood++;
                        world[i][j] = "wood";
                    }
                    else if (n == 3 && count_lake < 4)
                    {
                        count_lake++;
                        world[i][j] = "lake";
                    }
                    else
                    {
                        j--;
                        continue;
                    }
                }
            }
        }
    }
    world[0][0] = "INIT";
    world[4][4] = "GOAL";
}


int main()
{
    std::array<std::array<std::string, 5>, 5 > world;
    int costg1[5][5], costg2[5][5], costg3[5][5],left, right, down;
    int r1 = 0, cl1 = 0, v1 = 1, cost1 = 0, r2 = 0, cl2 = 0, v2 = 1, cost2 = 0, r3 = 0, cl3 = 0, v3 = 1, cost3 = 0;
    create_world(world);
    print_world(world);

    // robot 1
    for (int i = 0; i <= 4; i++)
    {
        for (int j = 0; j <= 4; j++)
        {
            costg1[i][j] = get_cost_from_robot_and_terrain(world[i][j], 1);
        }
    }

    // robot 2
    for (int i = 0; i <= 4; i++)
    {
        for (int j = 0; j <= 4; j++)
        {
            costg2[i][j] = get_cost_from_robot_and_terrain(world[i][j], 2);
        }
    }

    // robot 3
    for (int i = 0; i <= 4; i++)
    {
        for (int j = 0; j <= 4; j++)
        {
            costg3[i][j] = get_cost_from_robot_and_terrain(world[i][j], 3);
        }
    }

   

    cout << "Robot 1's path is ";
    for (int i=0; v1 != 0;i++) 
    {
        int right = costg1[r1][cl1+1];
        int down = costg1[r1+1][cl1];

        if (abs(right) < abs(down)) 
        {
            std::cout << "(" << r1 << "," << cl1 << ")->";
            cl1++;
            v1 = costg1[r1][cl1];
            cost1 = cost1 + costg1[r1][cl1];

        }
        else if (abs(right) > abs(down))
        {
            std::cout << "(" << r1 << "," << cl1 << ")->";
            r1++;
            v1 = costg1[r1][cl1];
            cost1 = cost1 + costg1[r1][cl1];
        }
        else
        {
            std::cout << "(" << r1 << "," << cl1 << ")->";
            r1++;
            v1 = costg1[r1][cl1];
            cost1 = cost1 + costg1[r1][cl1];
        }
    }

    std::cout << "(4,4) with a cummulative cost of " << cost1 << endl;

   

    std::cout << "Robot 2's path is ";
    for(int i=1; v2!= 0; i++)
    {
        right = costg2[r2][cl2+1];
        down = costg2[r2+1][cl2];

        if (abs(right) < abs(down))
        {
            std::cout << "(" << r2 << "," << cl2 << ")->";
            cl2++;
            v2 = costg2[r2][cl2];
            cost2 = cost2 + costg2[r2][cl2];
        }
        else if (abs(right) > abs(down))
        {
            std::cout << "(" << r2 << "," << cl2 << ")->";
            r2++;
            v2 = costg2[r2][cl2];
            cost2 = cost2 + costg2[r2][cl2];
        }
        else
        {
            std::cout << "(" << r2 << "," << cl2 << ")->";
            r2++;
            v2 = costg2[r2][cl2];
            cost2 = cost2 + costg2[r2][cl2];
        }
    }
    std::cout << "(4,4) with a cummulative cost of " << cost2 << endl;

    std ::cout << "Robot 3's path is ";
  
   for(int i=0;v3 != 0; i++)
    {
        right = costg3[r3][cl3+1];
        down = costg3[r3+1][cl3];

        if (abs(right) < abs(down))
        {
            std::cout << "(" << r3 << "," << cl3 << ")->";
            cl3++;
            v3 = costg3[r3][cl3];
            cost3 = cost3 + costg3[r3][cl3];
        }
        else if (abs(right) > abs(down))
        {
            std::cout << "(" << r3 << "," << cl3 << ")->";
            r3++;
            v3 = costg3[r3][cl3];
            cost3 = cost3 + costg3[r3][cl3];
        }
        else
        {
            std::cout << "(" << r3 << "," << cl3 << ")->";
            r3++;
            v3 = costg3[r3][cl3];
            cost3 = cost3 + costg3[r3][cl3];
        }
   }
    std::cout << "(4,4) with a cummulative cost of " << cost3 << endl;

    return 0;
}