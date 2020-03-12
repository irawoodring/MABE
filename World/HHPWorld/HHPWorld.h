//  MABE is a product of The Hintze Lab @ MSU
//     for general research information:
//         hintzelab.msu.edu
//     for MABE documentation:
//         github.com/Hintzelab/MABE/wiki
//
//  Copyright (c) 2015 Michigan State University. All rights reserved.
//     to view the full license, visit:
//         github.com/Hintzelab/MABE/wiki/License

#pragma once

#include "../AbstractWorld.h"
#include "../../Genome/CircularGenome/CircularGenome.h"

#include <cstdlib>
#include <thread>
#include <iostream>
#include <iomanip>

#include <vector>

class HHPWorld : public AbstractWorld {

	public:

		bool infect(const std::vector<bool> &key, const std::vector<bool> &lock, double percentage);
		static std::shared_ptr < ParameterLink<int>> worldXPL;
		static std::shared_ptr < ParameterLink<int>> worldYPL;
		int worldX;
		int worldY;

		static std::shared_ptr < ParameterLink<double>> mutationPointCatPL;
		static std::shared_ptr < ParameterLink<double>> mutationSizeCatPL;
		static std::shared_ptr < ParameterLink<double>> mutationPointDogPL;
		static std::shared_ptr < ParameterLink<double>> mutationSizeDogPL;
		static std::shared_ptr < ParameterLink<double>> mutationPointFleaPL;
		static std::shared_ptr < ParameterLink<double>> mutationSizeFleaPL;
		static std::shared_ptr < ParameterLink<int>> reproductionThresholdCatPL;
		static std::shared_ptr < ParameterLink<int>> reproductionThresholdDogPL;
		static std::shared_ptr < ParameterLink<double>> reproductionThresholdFleaPL;
		static std::shared_ptr < ParameterLink<double>> turnRateCatPL;
		static std::shared_ptr < ParameterLink<double>> turnRateDogPL;
		static std::shared_ptr < ParameterLink<double>> moveRateCatPL;
		static std::shared_ptr < ParameterLink<double>> moveRateDogPL;
		static std::shared_ptr < ParameterLink<int>> startingLockLengthCatPL;
		static std::shared_ptr < ParameterLink<int>> startingLockLengthDogPL;
		static std::shared_ptr < ParameterLink<int>> startingKeyLengthFleaPL;
		static std::shared_ptr < ParameterLink<double>> requiredMatchLengthCatPL;
		static std::shared_ptr < ParameterLink<double>> requiredMatchLengthDogPL;
		static std::shared_ptr < ParameterLink<double>> resourcesLostToFleasCatPL;
		static std::shared_ptr < ParameterLink<double>> resourcesLostToFleasDogPL;

		double mutationPointCat;
		double mutationSizeCat;
		double mutationPointDog;
		double mutationSizeDog;
		double mutationPointFlea;
		double mutationSizeFlea;
		int reproductionThresholdCat;
		int reproductionThresholdDog;
		double reproductionThresholdFlea;
		double turnRateCat;
		double turnRateDog;
		double moveRateCat;
		double moveRateDog;
		int startingLockLengthCat;
		int startingLockLengthDog;
		int startingKeyLengthFlea;
		double requiredMatchLengthCat;
		double requiredMatchLengthDog;
		double resourcesLostToFleasCat;
		double resourcesLostToFleasDog;

		static std::shared_ptr < ParameterLink<int>> recordImageStepPL;
		int recordImageStep;
		static std::shared_ptr < ParameterLink<int>> recordWorldStateStepPL;
		int recordWorldStateStep;
		static std::shared_ptr < ParameterLink<bool>> worldWrapsPL;
		bool worldWraps;

		enum class HostTag { noTag, catTag, dogTag };

		// Vector2d is wraps a vector<T> and provides x,y style access
		// no error checking is provided for out of range errors
		// internally this class uses R(ow) and C(olumn) (i.e. how the data is stored in the data vector)
		// the user sees x,y where x = column, y = row
		template <typename T> class Vector2d {
			std::vector<T> data;
			int R, C;

			// get index into data vector for a given x,y
			inline int getIndex(int r, int c) { return (r * C) + c; }

			public:
			Vector2d() {
				R = 0;
				C = 0;
			}
			// construct a vector of size x * y
			Vector2d(int x, int y) : R(y), C(x) { data.resize(R * C); }

			Vector2d(int x, int y, T value) : R(y), C(x) { data.resize(R * C, value); }

			void reset(int x, int y) {
				R = y;
				C = x;
				data.clear();
				data.resize(R * C);
			}

			void reset(int x, int y, T value) {
				R = y;
				C = x;
				data.clear();
				data.resize(R * C, value);
			}

			// overwrite this classes data (vector<T>) with data coppied from newData
			void assign(std::vector<T> newData) {
				if ((int)newData.size() != R * C) {
					std::cout << "  ERROR :: in Vector2d::assign() vector provided does not "
						"fit. provided vector is size "
						<< newData.size() << " but Rows(" << R << ") * Columns(" << C
						<< ") == " << R * C << ". Exitting." << std::endl;
					exit(1);
				}
				data = newData;
			}

			// provides access to value x,y can be l-value or r-value (i.e. used for
			// lookup of assignment)
			T& operator()(int x, int y) { return data[getIndex(y, x)]; }

			T& operator()(double x, double y) {
				return data[getIndex((int)(y), (int)(x))];
			}

			T& operator()(std::pair<int, int> loc) {
				return data[getIndex(loc.second, loc.first)];
			}

			T& operator()(std::pair<double, double> loc) {
				return data[getIndex((int)(loc.second), (int)(loc.first))];
			}

			// show the contents of this Vector2d with index values, and x,y values
			void show() {
				for (int r = 0; r < R; r++) {
					for (int c = 0; c < C; c++) {
						std::cout << getIndex(r, c) << " : " << c << "," << r << " : "
							<< data[getIndex(r, c)] << "\n";
					}
				}
			}

			// show the contents of this Vector2d in a grid
			void showGrid(int precision = -1) {
				if (precision < 0) {
					for (int r = 0; r < R; r++) {
						for (int c = 0; c < C; c++) {
							std::cout << data[getIndex(r, c)] << " ";
						}
						std::cout << "\n";
					}
				}
				else {
					for (int r = 0; r < R; r++) {
						for (int c = 0; c < C; c++) {
							if (data[getIndex(r, c)] == 0) {
								std::cout << std::setfill(' ') << std::setw((precision * 2) + 2)
									<< " ";
							}
							else {
								std::cout << std::setfill(' ') << std::setw((precision * 2) + 1)
									<< std::fixed << std::setprecision(precision)
									<< data[getIndex(r, c)] << " ";
							}
						}
						std::cout << "\n";
					}
				}
			}
			int x() { return C; }

			int y() { return R; }
		};


		class Parasite {
			public:
				std::shared_ptr<Organism> org;
				int timeOfDeath;

				double resource = 0;
				std::vector<bool> bitstring;

				Parasite() = delete;
				Parasite(std::shared_ptr<Organism> org_) : org(org_) {
					// FIX ME add parameters
					timeOfDeath = Random::getInt(Global::update + 20, Global::update + 30);
				}

				void mutate(double point, double size) {
					// Find out how many flips to flip
					int num = Random::getBinomial(bitstring.size(), point);
					for(int j=0; j<num; ++j){
						int index = Random::getInt(bitstring.size());
						bitstring[index] = !bitstring[index];
					} 		
				}

				void show() {
					std::cout << "     parasite org ID: " << org->ID << "   resource: " << resource << std::endl;
				}

				void show_infection(){
					std::cout << "\tHost org ID: " << org->ID << " is a parasite with key " << get_bitstring() << std::endl;
				}

				std::string get_bitstring(){
					std::string repr;
					for(auto i=bitstring.begin(); i<bitstring.end(); ++i){
						repr += (*i == true) ? "1":"0";
					}
					return repr;
				}
		};

		class Host {
			public:
				std::shared_ptr<Organism> org;
				std::vector<std::shared_ptr<Parasite>> parasites;
				std::vector<bool> bitstring;

				int timeOfDeath;
				int x, y;
				int direction;
				double resource = 0;

				HostTag tag;

				Host() = delete;
				Host(std::shared_ptr<Organism> org_, HostTag tag_, int x_ = 0, int y_ = 0, int direction_ = 0) : org(org_), tag(tag_), x(x_), y(y_), direction(direction_) {
					// Add min and max lifespans
					timeOfDeath = Random::getInt(Global::update + 20, Global::update + 30);
				}

				void mutate(double point, double size) {
					//std::cout << "Tag: " << (int)tag << " mutating." << std::endl;
					//if(tag == HostTag::dogTag)
					//	std::cout << "\t" << point << ", " << size << "." << std::endl;
					// Find out how many flips to flip
					int num = Random::getBinomial(bitstring.size(), point);
					for(int j=0; j<num; ++j){
						int index = Random::getInt(bitstring.size());
						bitstring[index] = !bitstring[index];
					} 		
				}

				void show() {
					std::cout << "   host org ID: " << org->ID << "  tag: " << static_cast<std::underlying_type<HostTag>::type>(tag) << "   loc: " << x << ", " << y << " direction: " << direction << "   resource: " << resource << std::endl;
					for (auto p : parasites) {
						p->show();
					}
				}

				void show_infection(){
					std::cout << "\tHost org ID: " << org->ID << " with tag: " << static_cast<std::underlying_type<HostTag>::type>(tag);
					if(tag == HostTag::catTag){
						std::cout << "(Cat) ";
					} else {
						std::cout << "(Dog) ";
					}
					std::cout << " has lock " << get_bitstring() << std::endl;
				}

				std::string get_bitstring(){
					std::string repr;
					for(auto i=bitstring.begin(); i<bitstring.end(); ++i){
						repr += (*i == true) ? "1":"0";
					}
					return repr;
				}
		};

		class Location {
			public:
				std::vector< std::shared_ptr<Host>> hosts; // hosts at this location
		};


		std::set<std::shared_ptr<Host>> catKillList;
		std::set<std::shared_ptr<Host>> dogKillList;
		std::set<std::shared_ptr<Parasite>> fleaKillList;

		std::vector<std::shared_ptr<Organism>> newPop;


		Vector2d<Location> world;

		std::shared_ptr<Host> garbageDog;
		std::shared_ptr<Host> garbageCat;
		std::shared_ptr<Host> garbageFlea;

		std::vector<std::shared_ptr<Host>> dogs;
		std::vector<std::shared_ptr<Host>> cats;
		std::vector<std::shared_ptr<Parasite>> fleas;


		int dx[8] = { 0,1,1,1,0,-1,-1,-1 }; // dx and dy provide movement for each of 8 directions.
		int dy[8] = { 1,1,0,-1,-1,-1,0,1 };

		void moveInWorld(std::shared_ptr<Host> h) {
			int destX = h->x + dx[h->direction]; // where will h be if they move in the direction they are facing?
			int destY = h->y + dy[h->direction];
			bool canMove = true;
			if (destX < 0 || destY < 0 || destX >= worldX || destY >= worldY){ // if the new location is off the world...
				if (worldWraps) {
					destX = loopMod(destX, worldX); // teleport acoss world!
					destY = loopMod(destY, worldY);
				}
				else { // h is stuck on a wall
					canMove = false;
				}
			}
			if (canMove) {
				//std::cout << "can move! " << h->x << ", " << h->y << "  --> " << destX << ", " << destY << std::endl;
				world(destX, destY).hosts.push_back(h); // add to new location
				world(h->x, h->y).hosts.erase(find(world(h->x, h->y).hosts.begin(), world(h->x, h->y).hosts.end(), h)); // remove from old location
				h->x = destX; // update h's own location
				h->y = destY;
				//std::cout << "did move. " << h->x << ", " << h->y << "  --> " << destX << ", " << destY << std::endl;
			}

		}

		//void saveWorldImage();

		double vectAve(std::vector<double> vect) {
			return std::accumulate(vect.begin(), vect.end(), 0.0) / static_cast<double>(vect.size());
		}

		// used when creating visualizations
		std::string visualizeData;

		double ave_fleas( std::vector<std::shared_ptr<Host>> hosts);
		HHPWorld(std::shared_ptr<ParametersTable> PT_ = nullptr);
		virtual ~HHPWorld() = default;

		void killHost(std::shared_ptr<Host>& host,
				std::vector<std::shared_ptr<Host>>& hosts, 
				std::set<std::shared_ptr<Host>>& killList);

		void killParasite(std::shared_ptr<Parasite>& parasite,
				std::shared_ptr<Host>& host,
				std::vector<std::shared_ptr<Parasite>>& parasites,
				std::set<std::shared_ptr<Parasite>>& killList);

		std::shared_ptr<Host> createCat(std::shared_ptr<Organism>& org, int x = -1, int y = -1, int direction = -1, bool initGenome = true);
		std::shared_ptr<Host> createDog(std::shared_ptr<Organism>& org, int x = -1, int y = -1, int direction = -1, bool initGenome = true);
		std::shared_ptr<Parasite> createFlea(std::shared_ptr<Organism>& org, std::shared_ptr<Host>& host, bool initGenome = true);

		void birthCat(std::shared_ptr<Host>& parent,int x = -1, int y = -1, int direction = -1);
		void birthDog(std::shared_ptr<Host>& parent, int x = -1, int y = -1, int direction = -1);
		void birthFlea(std::shared_ptr<Parasite>& parent, std::shared_ptr<Host>& host);

		void killCat(std::shared_ptr<Host>& cat);
		void killDog(std::shared_ptr<Host>& dog);
		void killFlea(std::shared_ptr<Parasite>& flea, std::shared_ptr<Host>& host);

		void jumpFlea(std::shared_ptr<Host> h1, std::shared_ptr<Host> h2); // jump flea from h1 to h2 (if h1 has fleas)
		void setupPopulations(std::map<std::string, std::shared_ptr<Group>>& groups,
				int analyze, int visualize, int debug);

		void updateHosts(std::vector < std::shared_ptr<Host>> hostList);

		void evaluate(std::map<std::string, std::shared_ptr<Group>>& groups,
				int analyze, int visualize, int debug);

		virtual std::unordered_map<std::string, std::unordered_set<std::string>>
			requiredGroups() override;
};

