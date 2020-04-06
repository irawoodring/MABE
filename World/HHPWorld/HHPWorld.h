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

#include <sstream>

#include <vector>

class HHPWorld : public AbstractWorld {

public:
	static std::shared_ptr < ParameterLink<int>> worldXPL;
	static std::shared_ptr < ParameterLink<int>> worldYPL;
	int worldX;
	int worldY;

	static std::shared_ptr < ParameterLink<std::string>> scoreListPL;

	static std::shared_ptr < ParameterLink<int>> cullParasitesToPL;


	static std::shared_ptr < ParameterLink<double>> mutationEraseRatePL;
	static std::shared_ptr < ParameterLink<std::string>> mutationPointCatPL;
	static std::shared_ptr < ParameterLink<std::string>> mutationSizeCatPL;
	static std::shared_ptr < ParameterLink<std::string>> mutationPointDogPL;
	static std::shared_ptr < ParameterLink<std::string>> mutationSizeDogPL;
	static std::shared_ptr < ParameterLink<std::string>> mutationPointFleaPL;
	static std::shared_ptr < ParameterLink<std::string>> mutationSizeFleaPL;
	static std::shared_ptr < ParameterLink<double>> reproductionThresholdCatPL;
	static std::shared_ptr < ParameterLink<double>> reproductionThresholdDogPL;
	static std::shared_ptr < ParameterLink<double>> reproductionThresholdFleaPL;
	static std::shared_ptr < ParameterLink<double>> turnRateCatPL;
	static std::shared_ptr < ParameterLink<double>> turnRateDogPL;
	static std::shared_ptr < ParameterLink<double>> moveRateCatPL;
	static std::shared_ptr < ParameterLink<double>> moveRateDogPL;
	static std::shared_ptr < ParameterLink<int>> initCatLockLengthPL;
	static std::shared_ptr < ParameterLink<int>> initDogLockLengthPL;
	static std::shared_ptr < ParameterLink<int>> initFleaKeyLengthPL;
	static std::shared_ptr < ParameterLink<std::string>> initCatLockPL;
	static std::shared_ptr < ParameterLink<std::string>> initDogLockPL;
	static std::shared_ptr < ParameterLink<std::string>> initFleaKeyPL;

	static std::shared_ptr < ParameterLink<double>> catFleaFeedAmtPL;
	static std::shared_ptr < ParameterLink<double>> dogFleaFeedAmtPL;
	static std::shared_ptr < ParameterLink<double>> catMaxToShareWithFleasPL;
	static std::shared_ptr < ParameterLink<double>> dogMaxToShareWithFleasPL;
	static std::shared_ptr < ParameterLink<double>> catParasiteInheritancePL;
	static std::shared_ptr < ParameterLink<double>> dogParasiteInheritancePL;
	static std::shared_ptr < ParameterLink<double>> resourceInflowPL;

	static std::shared_ptr < ParameterLink<std::string>> contactRateInSpeciesPL;
	static std::shared_ptr < ParameterLink<std::string>> contactRateAcrossSpeciesPL;
	static std::shared_ptr < ParameterLink<double>> transferRatePL;

	static std::shared_ptr < ParameterLink<double>> HostParasiteRelationshipPL;

	static std::shared_ptr < ParameterLink<double>> ParasitesStartOnCatsPL;

	double mutationEraseRate;

	double reproductionThresholdCat;
	double reproductionThresholdDog;
	double reproductionThresholdFlea;
	double turnRateCat;
	double turnRateDog;
	double moveRateCat;
	double moveRateDog;

	double catFleaFeedAmt;
	double dogFleaFeedAmt;
	double catMaxToShareWithFleas;
	double dogMaxToShareWithFleas;

	double resourceInflow;

	std::vector<double> contactRateInSpeciesList;
	std::vector<int> contactRateInSpeciesTimesList;
	double contactRateInSpecies;

	std::vector<double> contactRateAcrossSpeciesList;
	std::vector<int> contactRateAcrossSpeciesTimesList;
	double contactRateAcrossSpecies;


	std::vector<double> mutationPointCatList;
	std::vector<int> mutationPointCatTimesList;
	double mutationPointCat;

	std::vector<double> mutationSizeCatList;
	std::vector<int> mutationSizeCatTimesList;
	double mutationSizeCat;

	std::vector<double> mutationPointDogList;
	std::vector<int> mutationPointDogTimesList;
	double mutationPointDog;

	std::vector<double> mutationSizeDogList;
	std::vector<int> mutationSizeDogTimesList;
	double mutationSizeDog;

	std::vector<double> mutationPointFleaList;
	std::vector<int> mutationPointFleaTimesList;
	double mutationPointFlea;

	std::vector<double> mutationSizeFleaList;
	std::vector<int> mutationSizeFleaTimesList;
	double mutationSizeFlea;


	double transferRate;

	double HostParasiteRelationship;

	static std::shared_ptr < ParameterLink<int>> recordImageStepPL;
	int recordImageStep;
	static std::shared_ptr < ParameterLink<int>> recordWorldStateStepPL;
	int recordWorldStateStep;
	static std::shared_ptr < ParameterLink<int>> recordGenomesStepPL;
	int recordGenomesStep;
	static std::shared_ptr < ParameterLink<bool>> worldWrapsPL;
	bool worldWraps;

	int cullParasitesTo;

	double catParasiteInheritance;
	double dogParasiteInheritance;

	std::vector<double> scoreList;

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


	// convert a string with format [Time]X[VALUE],[TIME]X[VALUE],... into two lists valuesList and timesList
	void convertTemoporalList(std::string inputString, std::vector<double>& valuesList, std::vector<int>& timesList) {
		std::vector<std::string> tempListA;
		std::vector<std::string> tempListB;
		convertCSVListToVector(inputString, tempListA);
		for (auto A : tempListA) {
			convertCSVListToVector(A, tempListB, 'X');
			std::stringstream t_str(tempListB[0]);
			int t;
			t_str >> t;
			timesList.push_back(t);
			std::stringstream d_str(tempListB[1]);
			double v;
			d_str >> v;
			valuesList.push_back(v);
		}
	}

	// given a valuesList, a timeList, a counter, and a value, update value and counter from values and times lists if Global::update says it's time
	void advanceTemporalList(int& counter, double& value, std::vector<double>& valueList, std::vector<int>& timesList) {
		if (counter < timesList.size() && Global::update == timesList[counter]) {
			value = valueList[counter];
			counter++;
		}
	}

	double percentMatch(const std::vector<bool>& key, const std::vector<bool>& lock, std::vector<double>& scores) {
		int keySize = key.size();
		int lockSize = lock.size();
		if (keySize == 0 || keySize < lockSize) {
			return scores.back();
		}
		if (lockSize == 0) {
			return scores[0];
		}

		int max = 0;

		for (int kstart = 0; kstart < keySize - (lockSize - 1); ++kstart) {
			int matches = 0;
			for (int l = 0; l < lockSize; ++l) {
				matches += key[kstart + l] == lock[l];
			}
			max = std::max(max, matches);
		}
		if (scores.size() < lockSize) {
			std::vector<double> emptyVect((lockSize - scores.size()) + 1, scores.back());
			scores.insert(scores.end(), emptyVect.begin(), emptyVect.end());
		}
		return scores[lockSize - max]; // if all are correct return scores[0]
	}

	std::string serializeGenome(std::vector<bool> genome) {
		std::string s = "";
		for (auto v : genome) {
			s += std::to_string(v);
		}
		return s;
	}


	std::vector<bool> getBitString(int length, std::string init = "all_0") {
		if (init == "all_0") {
			return std::vector<bool>(length, 0);
		}
		if (init == "all_1") {
			return std::vector<bool>(length, 1);
		}
		if (init == "random") {
			std::vector<bool> bitstring(length);
			for (int i = 0; i < length; ++i) {
				bitstring[i] = Random::getInt(1);
			}
			return(bitstring);
		}
	}

	// given a vector<bool> apply point mutations at a persite rate of point,
	// and insertion/deletion at a rate of size
	void mutateBitString(std::vector<bool>& bitstring, double point, double size) {
		// Find out how many flips to flip
		//int num = Random::getBinomial(bitstring.size(), point);
		while (Random::P(point)) {
			int index = Random::getIndex(bitstring.size());
			bitstring[index] = !bitstring[index];
		}

		//num = Random::getBinomial(bitstring.size(), size);
		while (Random::P(size)) {
			if (Random::P(mutationEraseRate)) {
				if (bitstring.size() > 3) {
					if (Random::P(.5)) { // delete from begining
						bitstring.erase(bitstring.begin());
					}
					else { // delete from end
						bitstring.erase(bitstring.end());
					}
					bitstring.erase(bitstring.begin() + Random::getIndex(bitstring.size()));
				}
			}
			else {
				if (Random::P(.5)) { // insert at begining
					bitstring.insert(bitstring.begin(), Random::getInt(0, 1));
				}
				else { // insert at end
					bitstring.insert(bitstring.end(), Random::getInt(0, 1));
				}

			}
		}
	}

	class Parasite {
	public:
		static std::shared_ptr < ParameterLink<double>> fleaLifeMinPL;
		static std::shared_ptr < ParameterLink<double>> fleaLifeMaxPL;

		std::shared_ptr<Organism> org;
		int timeOfDeath;

		double resource = 0;
		std::vector<bool> bitstring;

		double collectedResource = 0;
		double bitStringMatch = 0;

		HostTag hostTag = HostTag::catTag;
		int hostID = -1;

		Parasite() = delete;
		Parasite(std::shared_ptr<Organism> org_) : org(org_) {
			timeOfDeath = Random::getInt(Global::update + fleaLifeMinPL->get(), Global::update + fleaLifeMaxPL->get());
		}

		void show() {
			std::cout << "     parasite org ID: " << org->ID << "   resource: " << resource << std::endl;
		}

		void show_infection() {
			std::cout << "\tHost org ID: " << org->ID << " is a parasite with key " << get_bitstring() << std::endl;
		}

		std::string get_bitstring() {
			std::string repr;
			for (auto i = bitstring.begin(); i < bitstring.end(); ++i) {
				repr += (*i == true) ? "1" : "0";
			}
			return repr;
		}
	};

	class Host {
	public:

		static std::shared_ptr < ParameterLink<double>> catLifeMinPL;
		static std::shared_ptr < ParameterLink<double>> catLifeMaxPL;
		static std::shared_ptr < ParameterLink<double>> dogLifeMinPL;
		static std::shared_ptr < ParameterLink<double>> dogLifeMaxPL;

		std::shared_ptr<Organism> org;
		std::vector<std::shared_ptr<Parasite>> parasites;
		std::vector<bool> bitstring;

		int timeOfDeath = 0;
		int x, y;
		int direction;
		double resource = 0;

		double collectedResource = 0;
		double theft = 0;
		double bitStringMatch = 0;

		HostTag tag;

		Host() = delete;
		Host(std::shared_ptr<Organism> org_, HostTag tag_, int x_ = 0, int y_ = 0, int direction_ = 0) : org(org_), tag(tag_), x(x_), y(y_), direction(direction_) {

			if (tag == HostTag::catTag) {
				timeOfDeath = Random::getInt(Global::update + catLifeMinPL->get(), Global::update + catLifeMaxPL->get());
			}
			if (tag == HostTag::dogTag) {
				timeOfDeath = Random::getInt(Global::update + dogLifeMinPL->get(), Global::update + dogLifeMaxPL->get());
			}
		}

		void show() {
			std::cout << "   host org ID: " << org->ID << "  tag: " << static_cast<std::underlying_type<HostTag>::type>(tag) << "   loc: " << x << ", " << y << " direction: " << direction << "   resource: " << resource << std::endl;
			for (auto p : parasites) {
				p->show();
			}
		}

		void show_infection() {
			std::cout << "\tHost org ID: " << org->ID << " with tag: " << static_cast<std::underlying_type<HostTag>::type>(tag);
			if (tag == HostTag::catTag) {
				std::cout << "(Cat) ";
			}
			else {
				std::cout << "(Dog) ";
			}
			std::cout << " has lock " << get_bitstring() << std::endl;
		}

		std::string get_bitstring() {
			std::string repr;
			for (auto i = bitstring.begin(); i < bitstring.end(); ++i) {
				repr += (*i == true) ? "1" : "0";
			}
			return repr;
		}
	};

	class Location {
	public:
		std::vector< std::shared_ptr<Host>> hosts; // hosts at this location
		int catCount = 0;
		int dogCount = 0;
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


	int catBirths = 0;
	int dogBirths = 0;
	int fleaBirths = 0;
	int catDeaths = 0;
	int dogDeaths = 0;
	int fleaDeaths = 0;
	int fleasInherited = 0;
	int fleaJumps = 0;
	int fleaJumpsAcross = 0;

	int dx[8] = { 0,1,1,1,0,-1,-1,-1 }; // dx and dy provide movement for each of 8 directions.
	int dy[8] = { 1,1,0,-1,-1,-1,0,1 };

	void moveInWorld(std::shared_ptr<Host> h) {
		int destX = h->x + dx[h->direction]; // where will h be if they move in the direction they are facing?
		int destY = h->y + dy[h->direction];
		bool canMove = true;
		if (destX < 0 || destY < 0 || destX >= worldX || destY >= worldY) { // if the new location is off the world...
			if (worldWraps) {
				destX = loopMod(destX, worldX); // teleport acoss world!
				destY = loopMod(destY, worldY);
			}
			else { // h is stuck on a wall
				canMove = false;
			}
		}
		if (canMove) {
			if (h->tag == HostTag::catTag) {
				world(h->x, h->y).catCount--;
				world(destX, destY).catCount++;
			}
			if (h->tag == HostTag::dogTag) {
				world(h->x, h->y).dogCount--;
				world(destX, destY).dogCount++;
			}
			//std::cout << "can move! direction: " << h->direction << "  " << h->x << ", " << h->y << "  --> " << destX << ", " << destY << std::endl;
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

	double ave_fleas(std::vector<std::shared_ptr<Host>> hosts);
	HHPWorld(std::shared_ptr<ParametersTable> PT_ = nullptr);
	virtual ~HHPWorld() = default;

	void killHost(std::shared_ptr<Host>& host,
		std::vector<std::shared_ptr<Host>>& hosts,
		std::set<std::shared_ptr<Host>>& killList);

	void killParasite(std::shared_ptr<Parasite>& parasite,
		std::shared_ptr<Host>& host,
		std::vector<std::shared_ptr<Parasite>>& parasites,
		std::set<std::shared_ptr<Parasite>>& killList);

	void createCat(std::shared_ptr<Organism>& org, int x = -1, int y = -1, int direction = -1, bool initGenome = true);
	void createDog(std::shared_ptr<Organism>& org, int x = -1, int y = -1, int direction = -1, bool initGenome = true);
	void createFlea(std::shared_ptr<Organism>& org, std::shared_ptr<Host>& host, bool initGenome = true);

	void birthCat(std::shared_ptr<Host>& parent, int x = -1, int y = -1, int direction = -1);
	void birthDog(std::shared_ptr<Host>& parent, int x = -1, int y = -1, int direction = -1);
	void birthFlea(std::shared_ptr<Parasite>& parent, std::shared_ptr<Host>& host);

	void killCat(std::shared_ptr<Host>& cat);
	void killDog(std::shared_ptr<Host>& dog);
	void killFlea(std::shared_ptr<Parasite>& flea, std::shared_ptr<Host>& host);

	void jumpFleas(std::shared_ptr<Host> h1, std::shared_ptr<Host> h2, double moveRate = -1.0);
	void migrateParasites(std::vector<std::shared_ptr<Host>>& hosts, double localContactRate);

	void setupPopulations(std::map<std::string, std::shared_ptr<Group>>& groups,
		int analyze, int visualize, int debug);

	void updateHosts(std::vector < std::shared_ptr<Host>> hostList);

	void evaluate(std::map<std::string, std::shared_ptr<Group>>& groups,
		int analyze, int visualize, int debug);

	virtual std::unordered_map<std::string, std::unordered_set<std::string>>
		requiredGroups() override;


	void testPercentMatch(std::vector<bool> key, std::vector<bool> lock, std::vector<double>& scores) {

		std::cout << "scores: ";
		for (auto x : scores) {
			std::cout << x << ",";
		}
		std::cout << "\n     key: ";
		for (auto x : key) {
			std::cout << x << ",";
		}
		std::cout << "\n    lock: ";
		for (auto x : lock) {
			std::cout << x << ",";
		}
		std::cout << "\n    -> " << percentMatch(key, lock, scores) << std::endl;
	}

	void tests() {
		std::vector<bool> lock;
		std::vector<bool> key;

		scoreList = { 1,.5 };
		lock = { 0,0,0 };
		key = { 0,0,0 };
		testPercentMatch(key, lock, scoreList);
		lock = { 0,0,0 };
		key = { 1,0,0 };
		testPercentMatch(key, lock, scoreList);
		lock = { 0,0,0 };
		key = { 1,1,0 };
		testPercentMatch(key, lock, scoreList);
		lock = { 0,0,0 };
		key = { 1,1,1 };
		testPercentMatch(key, lock, scoreList);
		scoreList = { 1,0,0,0 };
		testPercentMatch(key, lock, scoreList);

		exit(1);
	}
};

