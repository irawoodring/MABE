#include "HHPWorld.h"
//#include "../../Utilities/bitmap_image.hpp"

std::shared_ptr < ParameterLink<int>> HHPWorld::worldXPL =
Parameters::register_parameter("WORLD_HHP-worldX", 5,
		"size in X of world");
std::shared_ptr < ParameterLink<int>> HHPWorld::worldYPL =
Parameters::register_parameter("WORLD_HHP-worldY", 5,
		"size in Y of world");
std::shared_ptr < ParameterLink<int>> HHPWorld::recordImageStepPL =
Parameters::register_parameter("WORLD_HHP_IO-recordImageStep", -1,
		"record world images when update % recordImageStep == 0, if -1, do not record images.");
std::shared_ptr < ParameterLink<int>> HHPWorld::recordWorldStateStepPL =
Parameters::register_parameter("WORLD_HHP_IO-recordWorldStateStep", -1,
		"record world state csv when update % recordWorldStateStep == 0, if -1, do not record status.");
std::shared_ptr < ParameterLink<bool>> HHPWorld::worldWrapsPL =
Parameters::register_parameter("WORLD_HHP-worldWraps", true,
		"does the world wrap?");
std::shared_ptr < ParameterLink<double>> HHPWorld::mutationPointCatPL = 
Parameters::register_parameter("WORLD_HHP-mutationPointCat", 0.05,
		"the point flip per site mutation rate");
std::shared_ptr < ParameterLink<double>> HHPWorld::mutationSizeCatPL = 
Parameters::register_parameter("WORLD_HHP-mutationSizeCat", 0.001,
		"the insertion/deletion per site mutation rate");
std::shared_ptr < ParameterLink<double>> HHPWorld::mutationPointDogPL =
Parameters::register_parameter("WORLD_HHP-mutationPointDog", 0.05,
		"the point flip per site mutation rate");
std::shared_ptr < ParameterLink<double>> HHPWorld::mutationSizeDogPL =
Parameters::register_parameter("WORLD_HHP-mutationSizeDog", 0.001,
		"the point insertion/deletion per site mutation rate");
// Told Cliff I wouldn't forget to add the leading zero :)
std::shared_ptr < ParameterLink<double>> HHPWorld::mutationPointFleaPL =
Parameters::register_parameter("WORLD_HHP-mutationPointFlea", 0.05,
		"the point flip per site mutation rate");
std::shared_ptr < ParameterLink<double>> HHPWorld::mutationSizeFleaPL =
Parameters::register_parameter("WORLD_HHP-mutationSizeFlea", 0.001,
		"the point insertion/deletion per site mutation rate");
std::shared_ptr < ParameterLink<int>> HHPWorld::reproductionThresholdCatPL =
Parameters::register_parameter("WORLD_HHP-reproductionThresholdCat", 10,
		"required resources for a cat to reproduce");
std::shared_ptr < ParameterLink<int>> HHPWorld::reproductionThresholdDogPL =
Parameters::register_parameter("WORLD_HHP-reproductionThresholdDog", 10,
		"required resources for a dog to reproduce");
std::shared_ptr < ParameterLink<double>> HHPWorld::reproductionThresholdFleaPL =
Parameters::register_parameter("WORLD_HHP-reproductionThresholdFlea", .5,
		"required resources for a flea to reproduce");
std::shared_ptr < ParameterLink<double>> HHPWorld::turnRateCatPL =
Parameters::register_parameter("WORLD_HHP-turnRateCat", 0.1,
		"how often cats switch direction");
std::shared_ptr < ParameterLink<double>> HHPWorld::turnRateDogPL =
Parameters::register_parameter("WORLD_HHP-turnRateDog", 0.1,
		"how often dogs switch direction");
std::shared_ptr < ParameterLink<double>> HHPWorld::moveRateCatPL =
Parameters::register_parameter("WORLD_HHP-moveRateCat", 0.5,
		"move rate for cats");
std::shared_ptr < ParameterLink<double>> HHPWorld::moveRateDogPL =
Parameters::register_parameter("WORLD_HHP-moveRateDog", 0.5,
		"move rate for dogs");
std::shared_ptr < ParameterLink<int>> HHPWorld::startingLockLengthCatPL =
Parameters::register_parameter("WORLD_HHP-startingLockLengthCat", 1,
		"number of bits for a cat's beginning lock string");
std::shared_ptr < ParameterLink<int>> HHPWorld::startingLockLengthDogPL =
Parameters::register_parameter("WORLD_HHP-startingLockLengthDog", 5,
		"number of bits for a dog's beginning lock string");
std::shared_ptr < ParameterLink<int>> HHPWorld::startingKeyLengthFleaPL =
Parameters::register_parameter("WORLD_HHP-startingKeyLengthFlea", 5,
		"number of bits for a flea's beginning key string");
std::shared_ptr < ParameterLink<double>> HHPWorld::requiredMatchLengthCatPL =
Parameters::register_parameter("WORLD_HHP-requiredMatchLengthCat", 0.5,
		"percentage of lock necessary to match for a cat to be infected");
std::shared_ptr < ParameterLink<double>> HHPWorld::requiredMatchLengthDogPL =
Parameters::register_parameter("WORLD_HHP-requiredMatchLengthDog", 0.5,
		"percentage of lock necessary to match for a dog to be infected");
std::shared_ptr < ParameterLink<double>> HHPWorld::resourcesLostToFleasCatPL =
Parameters::register_parameter("WORLD_HHP-resourcesLostToFleasCat", 0.5,
		"percentage of resources a cat loses to fleas each update");
std::shared_ptr < ParameterLink<double>> HHPWorld::resourcesLostToFleasDogPL =
Parameters::register_parameter("WORLD_HHP-resourcesLostToFleasDog", 0.5,
		"percentage of resources a dog loses to fleas each update");
HHPWorld::HHPWorld(std::shared_ptr<ParametersTable> PT_)
	: AbstractWorld(PT_) {

		mutationPointCat = mutationPointCatPL->get(PT);
		mutationSizeCat = mutationSizeCatPL->get(PT);
		mutationPointDog = mutationPointDogPL->get(PT);
		mutationSizeDog = mutationSizeDogPL->get(PT);
		mutationPointFlea = mutationPointFleaPL->get(PT);
		mutationSizeFlea = mutationSizeFleaPL->get(PT);
		reproductionThresholdCat = reproductionThresholdCatPL->get(PT);
		reproductionThresholdDog = reproductionThresholdDogPL->get(PT);
		reproductionThresholdFlea = reproductionThresholdFleaPL->get(PT);
		turnRateCat = turnRateCatPL->get(PT);
		turnRateDog = turnRateDogPL->get(PT);
		moveRateCat = moveRateCatPL->get(PT);
		moveRateDog = moveRateDogPL->get(PT);
		startingLockLengthCat = startingLockLengthCatPL->get(PT);
		startingLockLengthDog = startingLockLengthDogPL->get(PT);
		startingKeyLengthFlea = startingKeyLengthFleaPL->get(PT);
		requiredMatchLengthCat = requiredMatchLengthCatPL->get(PT);
		requiredMatchLengthDog = requiredMatchLengthDogPL->get(PT);
		resourcesLostToFleasCat = resourcesLostToFleasCatPL->get(PT);
		resourcesLostToFleasDog = resourcesLostToFleasDogPL->get(PT);

		std::cout << "in HHPWorld constructor :: " << std::endl;

		worldX = worldXPL->get(PT);
		worldY = worldYPL->get(PT);
		std::cout << "Size " << worldX << ", " << worldY << std::endl;
		recordImageStep = recordImageStepPL->get(PT);
		recordWorldStateStep = recordWorldStateStepPL->get(PT);

		worldWraps = worldWrapsPL->get(PT);

		// columns to be added to ave file
		popFileColumns.clear();
		//popFileColumns.push_back("moo");
		//for (int i = 0; i < numberOfTraits; i++) {
		//	popFileColumns.push_back(traitNames[i]);
		//	popFileColumns.push_back(traitNames[i]+"_VAR");
		//popFileColumns.push_back(fitNames[i]);
		//}

	}

// create a Cat. cat will be added to cats and world.
// if x, y, direction are not provided, cat will be placed randomly in world
// genome will be randomized if initGenome = true (default)
std::shared_ptr<HHPWorld::Host> HHPWorld::createCat(std::shared_ptr<Organism>& org, int x, int y, int direction, bool initGenome) {
	//randomize genome
	//if (initGenome) {
	//	org->genomes["cat::"]->fillRandom();
	//}
	if (x == -1) {
		x = Random::getIndex(worldX);
	}
	if (y == -1) {
		y = Random::getIndex(worldY);
	}
	if (direction == -1) {
		direction = Random::getIndex(8);
	}
	// make a cat and place this in world
	auto newCat = std::make_shared<Host>(org, HostTag::catTag, x, y, direction);
	if(initGenome){
		newCat->bitstring = std::vector<bool>(Random::getInt(1,startingLockLengthCat));
		for(int i=0; i<newCat->bitstring.size(); ++i){
			newCat->bitstring[i] = Random::getInt(1);
		}
	} 

	cats.push_back(newCat);
	world(newCat->x, newCat->y).hosts.push_back(newCat);
	return newCat;
}

// create a Dog. dog will be added to dogs and world.
// if x, y, direction are not provided, dog will be placed randomly in world
// genome will be randomized if initGenome = true (default)
std::shared_ptr<HHPWorld::Host> HHPWorld::createDog(std::shared_ptr<Organism>& org, int x, int y, int direction, bool initGenome) {
	if (x == -1) {
		x = Random::getIndex(worldX);
	}
	if (y == -1) {
		y = Random::getIndex(worldY);
	}
	if (direction == -1) {
		direction = Random::getIndex(8);
	}
	// make a dog and place this in world
	auto newDog = std::make_shared<Host>(org, HostTag::dogTag, x, y, direction);
	if(initGenome){
		int length = Random::getInt(1, startingLockLengthDog);
		//std::cout << "Dog length is " << length << std::endl;
		newDog->bitstring = std::vector<bool>(length);
		for(int i=0; i<newDog->bitstring.size(); ++i){
			newDog->bitstring[i] = Random::getInt(1);
		}
	}

	dogs.push_back(newDog);
	world(newDog->x, newDog->y).hosts.push_back(newDog);
	return newDog;
}

// create a flea and place on the provided host
// flea will be added to fleas
// genome will be randomized if initGenome = true (default)
std::shared_ptr<HHPWorld::Parasite> HHPWorld::createFlea(std::shared_ptr<Organism>& org, std::shared_ptr<Host>& host, bool initGenome) {
	//randomize genome
	//if (initGenome) {
	//	org->genomes["flea::"]->fillRandom();
	//}
	// make a cat and place this in world
	auto newFlea = std::make_shared<Parasite>(org);
	//std::cout << "Making flea " << newFlea->org->ID << " on host " << host->org->ID << std::endl;
	newFlea->bitstring = std::vector<bool>(Random::getInt(1,startingKeyLengthFlea));
	for(int i=0; i<newFlea->bitstring.size(); ++i){
		newFlea->bitstring[i] = Random::getInt(1);
	}
	fleas.push_back(newFlea);
	host->parasites.push_back(newFlea);
	return newFlea;
}

// birth a cat given a parent
// this will also add this cat to cats and world
// if x, y and direction are not provided, x and y will = parent and direction will be random
// if x, y are provided, but direction is not provided, direction will be random
void HHPWorld::birthCat(std::shared_ptr<Host>& parent, int x, int y, int direction) {
	if (x == -1) {
		x = parent->x;
	}
	if (y == -1) {
		y = parent->y;
	}
	if (direction == -1) {
		direction = Random::getIndex(8);
	}
	// make a new mabe offspring org from parent org
	auto newOrg = parent->org->makeMutatedOffspringFrom(parent->org);
	// place in world in same location at parent with random direction
	auto newCat = createCat(newOrg, x, y, direction, true);
	newCat->bitstring = parent->bitstring;
	newCat->mutate(mutationPointCat, mutationSizeCat);
}

// birth a dog given a parent
// this will also add this dog to dogs and world
// if x, y and direction are not provided, x and y will = parent and direction will be random
// if x, y are provided, but direction is not provided, direction will be random
void HHPWorld::birthDog(std::shared_ptr<Host>& parent, int x, int y, int direction) {
	if (x == -1) {
		x = parent->x;
	}
	if (y == -1) {
		y = parent->y;
	}
	if (direction == -1) {
		direction = Random::getIndex(8);
	}
	// make a new mabe offspring org from parent org
	auto newOrg = parent->org->makeMutatedOffspringFrom(parent->org);
	// place in world in same location at parent with random direction
	auto newDog = createDog(newOrg, x, y, direction, true);
	newDog->bitstring = parent->bitstring;
	newDog->mutate(mutationPointDog, mutationSizeDog);
}

// birth a flea given a parent and host
// flea will be placed in the provided hosts parasite vector and fleas
void HHPWorld::birthFlea(std::shared_ptr<Parasite>& parent, std::shared_ptr<Host>& host) {
	// make a new mabe offspring org from parent org
	auto newOrg = parent->org->makeMutatedOffspringFrom(parent->org);
	auto newFlea = createFlea(newOrg, host, true);
	newFlea->bitstring = parent->bitstring;
	newFlea->mutate(mutationPointFlea, mutationSizeFlea);
}

// kill a host, this will:
//   a) remove host from the provided hosts list
//   b) add host to provided kill list
//   c) remove host from world
// host org will still be in population so it will be saved on the next call to archive
void HHPWorld::killHost(std::shared_ptr<Host>& host,
		std::vector<std::shared_ptr<Host>>& hosts,
		std::set<std::shared_ptr<Host>>& killList) {
	// move to kill list
	killList.insert(host);

	// locat host in world location
	//std::cout << "removing host " << host->org->ID << " at location: " << host->x << ", " << host->y << std::endl;
	//std::cout << "ID's at this location: ";
	//for (auto xxx : world(host->x, host->y).hosts) {
	//	std::cout << xxx->org->ID << "  ";
	//}
	//std::cout << std::endl;
	auto it = std::find(world(host->x, host->y).hosts.begin(), world(host->x, host->y).hosts.end(), host);
	if (it == world(host->x, host->y).hosts.end()) {
		std::cout << "    in HHPWorld::killHost() :: host was not in world location! exiting..." << std::endl;
		exit(1);
	}

	// remove host form world
	world(host->x, host->y).hosts.erase(it);

	// find this host in the provided hosts list
	it = std::find(hosts.begin(), hosts.end(), host);
	if (it == hosts.end()) {
		std::cout << "    in HHPWorld::killHost() :: host was not in provided hosts vector! exiting..." << std::endl;
		exit(1);
	}

	// OMG IS IT AN ITERATOR ISSUE?
	// Always dies on the last element.  Shows up 
	int size = host->parasites.size();
	for (int i = host->parasites.size() - 1; i>=0 ; i--) {
		//host->parasites[0]->show();
		//std::cout << "----------" << std::endl;
		killParasite(host->parasites[i],host,fleas,fleaKillList);
	}
	//std::cout << "SIZE OF LIST IS NOW " << host->parasites.size() << std::endl;


	// remove from provided host list
	hosts.erase(it);
}

// kill a parasite, this will:
//   a) remove parasite from the provided parasite list
//   b) add parasite to provided kill list
//   c) remove parasite from from provided hosts parasite list
// parasite org will still be in population so it will be saved on the next call to archive
void HHPWorld::killParasite(std::shared_ptr<Parasite>& parasite,
		std::shared_ptr<Host>& host, 
		std::vector<std::shared_ptr<Parasite>>& parasites,
		std::set<std::shared_ptr<Parasite>>& killList) {

	// move to kill list
	killList.insert(parasite);

	// find in host
	auto it = std::find(host->parasites.begin(), host->parasites.end(), parasite);
	if (it == host->parasites.end()) {
		std::cout << "    in HHPWorld::killParasite() :: parasite " << parasite->org->ID << " was not in provided parasite vector on provided host! exiting..." << std::endl;
		exit(1);
	}
	else {
		// remove from host
		host->parasites.erase(it);
	}
	// find this parasite in the provided parasites list
	it = std::find(parasites.begin(), parasites.end(), parasite);
	if (it == parasites.end()) {
		std::cout << "    in HHPWorld::killParasite() :: parasite " << parasite->org->ID << "  was not in provided parasites vector! exiting..." << std::endl;
		exit(1);
	}
	else {
		parasites.erase(it);
	}
}

// kill a cat, see killHost
void HHPWorld::killCat(std::shared_ptr<Host>& cat) {
	killHost(cat, cats, catKillList);
}

// kill a dog, see killHost
void HHPWorld::killDog(std::shared_ptr<Host>& dog) {
	killHost(dog, dogs, dogKillList);
}

// kill a flea, see killParasite
void HHPWorld::killFlea(std::shared_ptr<Parasite>& flea, std::shared_ptr<Host>& host) {
	killParasite(flea, host, fleas, fleaKillList);
}

// setupPopulations is called from evaluate and is used to convert mabe
// groups to Hosts (cats, dogs) and Parasites (fleas)
void HHPWorld::setupPopulations(std::map<std::string, std::shared_ptr<Group>>& groups,
		int analyze, int visualize, int debug) {
	std::cout << "Starting with cat pop " << groups["cat::"]->population.size() << std::endl;
	for (auto org : groups["cat::"]->population) {
		createCat(org);
	}
	std::cout << "Starting with dog pop " << groups["dog::"]->population.size() << std::endl;
	for (auto org : groups["dog::"]->population) {
		createDog(org);
	}
	std::cout << "Starting with flea pop " << groups["flea::"]->population.size() << std::endl;
	for (auto org : groups["flea::"]->population) {
		// create a flea from org on a random cat (poor thing...)
		createFlea(org, cats[Random::getIndex(cats.size())]);
	}
}

void HHPWorld::updateHosts(std::vector < std::shared_ptr<Host>> hostList) {

	std::vector < std::shared_ptr<Host>> localHostKillList;
	std::vector < std::shared_ptr<Host>> localHostParentList;
	std::vector < std::shared_ptr<Parasite>> localParasiteKillList;
	std::vector < std::pair<std::shared_ptr<Parasite>, std::shared_ptr<Host>>> localParasiteParentList;

	for (int hostIndex = 0; hostIndex < hostList.size(); hostIndex++) {
		auto h = hostList[hostIndex];
		// Random host death or livespan over.
		if (Random::P(.05) || h->timeOfDeath <= Global::update) {
			//localHostKillList.push_back(h); // don't kill them yet... it'll mess up the interation!
		}

		else {
			h->resource += 1; // eat something (you're all skin and bones!)
			double resourcesLostPercentage = resourcesLostToFleasCat;
			if (h->tag == HostTag::dogTag){
				resourcesLostPercentage = resourcesLostToFleasDog;
			}
			double lostResources = h->resource * resourcesLostPercentage;
			//std::cout << resourcesLostPercentage << " Losing " << lostResources << "." << std::endl;
			if( h->resource > 0){
				for (auto p : h->parasites) {
					// How many resources lost to parasites
					p->resource += lostResources / h->parasites.size();
					//std::cout << "Parasite has " << lostResources / h->parasites.size() << " food." << std::endl;
					h->resource -= lostResources / h->parasites.size();
					// CAN PARASITE REPRODUCE?
					if(p->resource > reproductionThresholdFlea){
						localParasiteParentList.push_back({p,h});
						p->resource -= reproductionThresholdFlea;
					}
				}
			}
			if(h->resource < 0){
				std::cout << h->org->ID << " STARVED with " << h->resource << "resources." << std::endl;
				localHostKillList.push_back(h);
			}

			// Check reproduction
			int reproductionCost = reproductionThresholdDog;
			if (h->tag == HostTag::catTag){
				reproductionCost = reproductionThresholdCat;
			}
			// If we got the resources, reproduce
			if (h->resource > reproductionCost){
				localHostParentList.push_back(h);	
				h->resource -= reproductionCost;
			}

			// Move hosts
			double turnRate = turnRateCat;
			double moveRate = moveRateCat;
			if (h->tag == HostTag::dogTag){
				turnRate = turnRateDog;
				moveRate = moveRateDog;
			}

			if (Random::P(turnRate)) { // with probability turnRate turn left of right 45 degrees
				h->direction += loopMod((h->direction + Random::getIndex(2) * 2) - 1, 8); // i.e. direction +/- 1
			}
			if (Random::P(moveRate)) { // with probability moveRate move forward
				moveInWorld(h);
			}
		}
	}
	// now kill the ones that died.
	for (auto h : localHostKillList) {
		if (h->tag == HostTag::catTag) {
			killCat(h); // kill a cat, and it's parasites
		}
		else {
			killDog(h); // kill a dog, and it's parasites
		}
	}

	// Birth some babies
	// for both hosts and parasites
	for(auto h : localHostParentList ){
		if(h->tag == HostTag::dogTag){
			birthDog(h);
		} else {
			birthCat(h);
		}
	}
	for(auto p : localParasiteParentList){
		birthFlea(p.first, p.second);
	}
}

void HHPWorld::jumpFlea(std::shared_ptr<Host> h1, std::shared_ptr<Host> h2) { // jump flea from h1 to h2 (if h1 has fleas)
	if (h1->parasites.size() > 0) { // if doner has parasites
		//int jumperIndex = Random::getIndex(h1->parasites.size()); // get an index for a parasite on doner
		//h2->parasites.push_back(h1->parasites[jumperIndex]); // jump parasite to the reciver
		//h1->parasites.erase(h1->parasites.begin() + jumperIndex); // remove parasite from doner

		for(auto i=0; i<h1->parasites.size(); ++i){
			double matchPercentage = requiredMatchLengthCat;
			if (h2->tag == HostTag::dogTag){
				matchPercentage = requiredMatchLengthDog;
			} 
			if(infect(h1->parasites[i]->bitstring, h2->bitstring, matchPercentage)){
				h2->parasites.push_back(h1->parasites[i]);
				h1->parasites.erase(h1->parasites.begin() + i);
			}
		}
	} // else do nothing... no parasites on h1
}

void HHPWorld::evaluate(std::map<std::string, std::shared_ptr<Group>>& groups,
		int analyze, int visualize, int debug) {

	std::cout << "  HHPWorld :: starting evaluation" << std::endl;

	// initalize world
	world.reset(worldX, worldY);

	// convert mabe populatoins to cats, dogs, and fleas
	setupPopulations(groups, analyze, visualize, debug);

	std::cout << "           :: setup done" << std::endl;

	// run the evaluation until time runs out...
	do {

		// update all hosts (death, resource, movement)
		updateHosts(cats);
		updateHosts(dogs);

		// parasite migration
		for (int y = 0; y < worldY; y++) { // for all locations in the world
			for (int x = 0; x < worldX; x++) {
				if (world(x, y).hosts.size() > 1) { // if there are atlease 2 hosts here
					std::shared_ptr<Host> h1 = world(x, y).hosts[Random::getIndex(world(x, y).hosts.size())]; // doner host
					std::shared_ptr<Host> h2;
					do {
						h2 = world(x, y).hosts[Random::getIndex(world(x, y).hosts.size())]; // reciver host
					} while (h1 == h2); // keep picking until doner != reciver
					jumpFlea(h1, h2);
				}
			}
		}


		// save image of world
		// this calls saveWorldImage which is currently written for MultiCellWorld
		if (recordImageStep > 0 && Global::update % recordImageStep == 0) {
			//saveWorldImage();
		}

		// save some world details to a csv file
		if (recordWorldStateStep > 0 && Global::update % recordWorldStateStep == 0) {

			//std::string headerString = "update,";
			//std::string dataString = std::to_string(Global::update) + ",";

			//FileManager::writeToFile("MultiCellReport.csv", dataString, headerString);
		}

		if (debug) { // generate a report to help debug
			for (int y = 0; y < worldY; y++) {
				for (int x = 0; x < worldX; x++) {
					std::cout << "loc: " << x << "," << y << std::endl;
					for (auto h : world(x, y).hosts) {
						h->show();
					}
				}
			}
		}

		// record population data with archivist
		//std::cout << "           :: starting archive" << std::endl;

		if (groups["cat::"]->population.size() > 0) {
			groups["cat::"]->archive();
		}
		else {
			//groups["cat::"]->archivist->finished_ = true;
		}
		if (groups["dog::"]->population.size() > 0) {
			groups["dog::"]->archive();
		}
		else {
			//groups["dog::"]->archivist->finished_ = true;
		}
		if (groups["flea::"]->population.size() > 0) {
			groups["flea::"]->archive();
		}
		else {
			//groups["flea::"]->archivist->finished_ = true;
		}
		//std::cout << "           :: archive done" << std::endl;


		// We need to update the mabe populations (i.e. group["name::"]->population) to remove any
		// orgs that have been added to a kill list. Orgs being killed should have been removed from the world
		// and the host or parasite lists before we get here (or bad things will result).
		// in other worlds, at this point, the world, the hosts (dog,cat) and parasites (flea) lists and
		// the hosts local parasite lists should all be correct.
		// All we should need to do is iterate over these lists and place any orgs we find into their proper populations,
		// and then make sure that kill is called on any orgs that are in host or parasite kill lists.

		//std::cout << "           :: clean up mabe populations : cats" << std::endl;

		// for each host and parasite group, collect living orgs into new populations
		// swap these with group->population to update population lists
		// iterate over killLists and call kill on mabe organisms so they can be deleted
		// clear killLists so that the hosts and parasites memory can be released.
		newPop.clear();
		for (auto host : cats) {
			newPop.push_back(host->org);
		}
		groups["cat::"]->population = newPop;

		//std::cout << "           :: clean up mabe populations : dogs" << std::endl;
		newPop.clear();
		for (auto host : dogs) {
			newPop.push_back(host->org);
		}
		groups["dog::"]->population = newPop;

		//std::cout << "           :: clean up mabe populations : fleas" << std::endl;
		newPop.clear();
		for (auto parasite : fleas) {
			newPop.push_back(parasite->org);
			//parasite->show();
		}
		groups["flea::"]->population = newPop;

		//std::cout << "           :: killing : cats" << std::endl;
		// now kill everyone in kill lists so that the memory can be reused
		for (auto beast : catKillList) {
			beast->org->kill();
		}
		catKillList.clear();

		//std::cout << "           :: killing : dogs" << std::endl;
		for (auto beast : dogKillList) {
			beast->org->kill();
		}
		dogKillList.clear();

		//std::cout << "           :: killing : fleas" << std::endl;
		for (auto beast : fleaKillList) {
			beast->org->kill();
		}
		fleaKillList.clear();

		// print a short accounting to terminal
		std::cout << "finished update: " << Global::update 
			<< "  cat pop size: " << cats.size()
			<< "  dog pop size: " << dogs.size() 
			<< "  flea pop size: " << fleas.size() 
			<< std::endl;

		//int total_cat = 0;
		//for(auto cat : cats){
		//	total_cat += cat->parasites.size();
		//	//std::cout << "Cat has " << cat->parasites.size() << " fleas." << std::endl;
		//}
		//int total_dog = 0;
		//for(auto dog : dogs){
		//	total_dog += dog->parasites.size();
		//std::cout << "Dog has " << dog->parasites.size() << " fleas." << std::endl;
		//}
		//std::cout << fleas.size() << " - " << total_cat + total_dog << " = " << fleas.size() - total_cat - total_dog << std::endl;
		std::cout << "Average fleas per cat: " << ave_fleas(cats) << std::endl;
		std::cout << "Average fleas per dog: " << ave_fleas(dogs) << std::endl;

		int string_size;
		for(auto i=cats.begin(); i!=cats.end();++i){
			string_size += (*i)->bitstring.size();
		}
		std::cout << "Average lock size for cats is " << string_size / cats.size() << std::endl;

		string_size = 0;
		for(auto i=dogs.begin(); i!=dogs.end();++i){
			string_size += (*i)->bitstring.size();
		}
		std::cout << "Average lock size for dogs is " << string_size / dogs.size() << std::endl;


		string_size = 0;
		for(auto i=fleas.begin(); i!=fleas.end();++i){
			string_size += (*i)->bitstring.size();
		}
		std::cout << "Average lock size for fleas is " << string_size / fleas.size() << std::endl;

		/*
		   for(auto flea : fleas){
		   bool found = false;
		   for(auto host : cats){
		   auto it = std::find(host->parasites.begin(), host->parasites.end(), flea);
		   if(it != host->parasites.end()){
		   found = true;
		   }
		   }
		   for(auto host : dogs){
		   auto it = std::find(host->parasites.begin(), host->parasites.end(), flea);
		   if(it != host->parasites.end()){
		   found = true;
		   }
		   }
		// Brute force method to cleanup fleas that
		// aren't on a host (for some fucking reason...)
		if(!found){
		//std::cout << "NOT FOUND: ";
		//flea->show();
		flea->org->kill();
		}
		}
		 */


		// advance time
		Global::update++;

		// keep going until the archivist say we are done.
	} while (!groups["cat::"]->archivist->finished_ && !groups["dog::"]->archivist->finished_ && !groups["flea::"]->archivist->finished_);
	std::cout << "finished run!" << std::endl;
}

std::unordered_map<std::string, std::unordered_set<std::string>>
HHPWorld::requiredGroups() {
	return { {"cat::",{}}, {"dog::",{}}, {"flea::",{}} };
	// this world needs cats, dogs and fleas, each with a genome with the same name...
}

bool
HHPWorld::infect(const std::vector<bool> &key, const std::vector<bool> &lock, double percentage){
	int m = key.size();
	int n = lock.size();
	if(m == 0 || n == 0){
		return false;
	}
	int* match = new int[(m+1)*(n+1)]();
	int max = 0;

	for(int i=0; i<=m; ++i){
		for(int j=0; j<=n; ++j){
			if(i == 0 || j == 0){
				match[i * n + j] = 0;
				continue;
			}
			if( key[i-1] == lock[j-1] ){
				match[i * n + j] = match[(i-1)*n+(j-1)] + 1;
				max = std::max(max, match[i*n+j]);
			} else {
				match[i*n+j] = 0;
			}
		}
	}
	delete[] match;
	int needed_length = m * percentage;
	if(max >= needed_length){
		return true;
	}
	return false;
}

double
HHPWorld::ave_fleas(std::vector<std::shared_ptr<Host>> hosts){
	double sum;
	for(int i=0; i<hosts.size(); ++i){
		sum += hosts[i]->parasites.size();
	}
	return sum / hosts.size();
}

/*
   void HHPWorld::saveWorldImage() {
   double cX = 1000;
   double cY = 1000;

   cartesian_canvas canvas(cX,cY);

   canvas.pen_color(0, 0, 0);
   canvas.fill_rectangle(-1 * (cX / 2), -1 * (cY / 2), cX/2, cY/2);

   double multiCellWidth = (cX / worldX);
   double multiCellHeight = (cY / worldY);

   double cellWidth = (multiCellWidth / multiCellX);
   double cellHeight = (multiCellHeight / multiCellY);

   double x1, x2, y1, y2;
   double multiCellX1, multiCellY1;
   for (int wY = 0; wY < worldY; wY++) {
   for (int wX = 0; wX < worldX; wX++) {
   if (!world(wX, wY).empty) {
   x1 = (wX * multiCellWidth) - (cX / 2);
   y1 = (wY * multiCellHeight) - (cY / 2);
   x2 = x1 + multiCellWidth;
   y2 = y1 + multiCellHeight;

   canvas.pen_color(255, 255, 255);
   canvas.fill_rectangle(x1,y1,x2,y2);
//std::cout << "draw multi cell : " << x1 << ", " << y1 << ", " << x2 << ", " << y2 << std::endl;
multiCellX1 = wX * multiCellWidth;
multiCellY1 = wY * multiCellHeight;

for (int y = 0; y < multiCellY; y++) {
for (int x = 0; x < multiCellX; x++){
if (!world(wX, wY).cells(x, y).empty) {
x1 = multiCellX1 + x * cellWidth - (cX / 2);
y1 = multiCellY1 + y * cellHeight - (cY / 2);
x2 = x1 + cellWidth;
y2 = y1 + cellHeight;
if (world(wX, wY).cells(x, y).evil) {
canvas.pen_color(255, 0, 0);
}
else if (world(wX, wY).cells(x, y).murder) {
canvas.pen_color(125, 0, 0);
}
else if (world(wX, wY).cells(x, y).first) {
canvas.pen_color(0, 0, 255);
}
else {
canvas.pen_color(0, 255, 0);
}
canvas.fill_rectangle(x1, y1, x2, y2);
//std::cout << "  draw cell : " << x1 << ", " << y1 << ", " << x2 << ", " << y2 << std::endl;

}
}
}
}
}
}

// add a grid
canvas.pen_color(0, 0, 0);
double pos = -1 * (cX / 2);
while (pos < (cX / 2)) {
canvas.fill_rectangle(pos-1, -1 * (cY / 2), pos, (cY / 2));
pos += multiCellWidth;
}
pos = -1 * (cY / 2);
while (pos < (cY / 2)) {
canvas.fill_rectangle(-1 * (cX / 2), pos-1, (cX / 2), pos);
pos += multiCellHeight;
}
canvas.image().save_image("output_"+std::to_string(100000+Global::update)+".bmp");
}
*/
