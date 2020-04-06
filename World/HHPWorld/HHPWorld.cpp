#include "HHPWorld.h"
//#include "../../Utilities/bitmap_image.hpp"

std::shared_ptr < ParameterLink<int>> HHPWorld::worldXPL =
Parameters::register_parameter("WORLD_HHP_SPACE-worldX", 15, "size in X of world");
std::shared_ptr < ParameterLink<int>> HHPWorld::worldYPL =
Parameters::register_parameter("WORLD_HHP_SPACE-worldY", 15, "size in Y of world");
std::shared_ptr < ParameterLink<bool>> HHPWorld::worldWrapsPL =
Parameters::register_parameter("WORLD_HHP_SPACE-worldWraps", true,
		"does the world wrap?");

std::shared_ptr < ParameterLink<int>> HHPWorld::recordImageStepPL =
Parameters::register_parameter("WORLD_HHP_IO-recordImageStep", -1,
		"record world images when update % recordImageStep == 0, if -1, do not record images");
std::shared_ptr < ParameterLink<int>> HHPWorld::recordWorldStateStepPL =
Parameters::register_parameter("WORLD_HHP_IO-recordWorldStateStep", -1,
		"record world state csv when update % recordWorldStateStep == 0, if -1, do not record status");
std::shared_ptr < ParameterLink<int>> HHPWorld::recordGenomesStepPL =
Parameters::register_parameter("WORLD_HHP_IO-recordGenomesStep", -1,
	"record genomes csv when update % recordGenomesStep == 0, if -1, do not record status");

std::shared_ptr < ParameterLink<std::string>> HHPWorld::scoreListPL =
Parameters::register_parameter("WORLD_HHP_TUNING-scoreList", (std::string)"1.0,0.5,0.1",
	"When bitStrings are compaired, scoreList determins return values, where:\n"
	"scoreList[0] is the value if there is a perfect match,\n"
	"scoreList[1] is the value if the match is off by 1, etc.\n"
	"The last number in the list will be repreated if more values are needed");
std::shared_ptr < ParameterLink<double>> HHPWorld::mutationEraseRatePL = 
Parameters::register_parameter("WORLD_HHP_TUNING-mutationEraseRate", 0.75,
		"when genomes experiance insertion/deletion mutations, they will delete at this rate");

std::shared_ptr < ParameterLink<std::string>> HHPWorld::mutationPointCatPL = 
Parameters::register_parameter("WORLD_HHP_MUTATION-mutationPointCat", (std::string)"0X0.005",
		"the point flip per site mutation rate");
std::shared_ptr < ParameterLink<std::string>> HHPWorld::mutationSizeCatPL =
Parameters::register_parameter("WORLD_HHP_MUTATION-mutationSizeCat", (std::string)"0X0",
		"the insertion/deletion per site mutation rate");
std::shared_ptr < ParameterLink<std::string>> HHPWorld::mutationPointDogPL =
Parameters::register_parameter("WORLD_HHP_MUTATION-mutationPointDog", (std::string)"0X0.005",
		"the point flip per site mutation rate");
std::shared_ptr < ParameterLink<std::string>> HHPWorld::mutationSizeDogPL =
Parameters::register_parameter("WORLD_HHP_MUTATION-mutationSizeDog", (std::string)"0X0",
		"the point insertion/deletion per site mutation rate");
std::shared_ptr < ParameterLink<std::string>> HHPWorld::mutationPointFleaPL =
Parameters::register_parameter("WORLD_HHP_MUTATION-mutationPointFlea", (std::string)"0X.025",
		"the point flip per site mutation rate");
std::shared_ptr < ParameterLink<std::string>> HHPWorld::mutationSizeFleaPL =
Parameters::register_parameter("WORLD_HHP_MUTATION-mutationSizeFlea", (std::string)"0X.01",
		"the point insertion/deletion per site mutation rate");
std::shared_ptr < ParameterLink<double>> HHPWorld::reproductionThresholdCatPL =
Parameters::register_parameter("WORLD_HHP_CATS-reproductionThresholdCat", 150.0,
		"required resources for a cat to reproduce");
std::shared_ptr < ParameterLink<double>> HHPWorld::reproductionThresholdDogPL =
Parameters::register_parameter("WORLD_HHP_DOGS-reproductionThresholdDog", 150.0,
		"required resources for a dog to reproduce");
std::shared_ptr < ParameterLink<double>> HHPWorld::reproductionThresholdFleaPL =
Parameters::register_parameter("WORLD_HHP_FLEAS-reproductionThresholdFlea", .1,
		"required resources for a flea to reproduce");
std::shared_ptr < ParameterLink<double>> HHPWorld::turnRateCatPL =
Parameters::register_parameter("WORLD_HHP_SPACE-turnRateCat", 0.1,
		"how often cats switch direction");
std::shared_ptr < ParameterLink<double>> HHPWorld::turnRateDogPL =
Parameters::register_parameter("WORLD_HHP_SPACE-turnRateDog", 0.1,
		"how often dogs switch direction");
std::shared_ptr < ParameterLink<double>> HHPWorld::moveRateCatPL =
Parameters::register_parameter("WORLD_HHP_SPACE-moveRateCat", 0.33,
		"move rate for cats");
std::shared_ptr < ParameterLink<double>> HHPWorld::moveRateDogPL =
Parameters::register_parameter("WORLD_HHP_SPACE-moveRateDog", 0.33,
		"move rate for dogs");
std::shared_ptr < ParameterLink<int>> HHPWorld::initCatLockLengthPL =
Parameters::register_parameter("WORLD_HHP_GENETICS-initCatLockLength", 3,
		"number of bits for a cat's beginning lock string");
std::shared_ptr < ParameterLink<int>> HHPWorld::initDogLockLengthPL =
Parameters::register_parameter("WORLD_HHP_GENETICS-initDogLockLength", 3,
		"number of bits for a dog's beginning lock string");
std::shared_ptr < ParameterLink<int>> HHPWorld::initFleaKeyLengthPL =
Parameters::register_parameter("WORLD_HHP_GENETICS-initFleaKeyLength", 5,
		"number of bits for a flea's beginning key string");

std::shared_ptr < ParameterLink<std::string>> HHPWorld::initCatLockPL =
Parameters::register_parameter("WORLD_HHP_GENETICS-initCatLock", (std::string)"all_0",
	"how should cat keys be initialized (all_0,all_1, or random)");
std::shared_ptr < ParameterLink<std::string>> HHPWorld::initDogLockPL =
Parameters::register_parameter("WORLD_HHP_GENETICS-initDogLock", (std::string)"all_0",
	"how should cat keys be initialized (all_0,all_1, or random)");
std::shared_ptr < ParameterLink<std::string>> HHPWorld::initFleaKeyPL =
Parameters::register_parameter("WORLD_HHP_GENETICS-initFleaKey", (std::string)"all_0",
	"how should cat keys be initialized (all_0,all_1, or random)");


std::shared_ptr < ParameterLink<double>> HHPWorld::catFleaFeedAmtPL = 
Parameters::register_parameter("WORLD_HHP_CATS-catFleaFeedAmt", .05,
	"percentage of a cats resources one parasite will take with a perfect match");

std::shared_ptr < ParameterLink<double>> HHPWorld::dogFleaFeedAmtPL =
Parameters::register_parameter("WORLD_HHP_DOGS-dogFleaFeedAmt", .05,
	"percentage of a dogs resources one parasite will take with a perfect match");

std::shared_ptr < ParameterLink<double>> HHPWorld::catMaxToShareWithFleasPL =
Parameters::register_parameter("WORLD_HHP_CATS-catMaxToShareWithFleas", 1.0,
	"total % of a cats resource that can be taken by fleas. If fleas would take more then this amount, fleas consumption is normalized");

std::shared_ptr < ParameterLink<double>> HHPWorld::dogMaxToShareWithFleasPL =
Parameters::register_parameter("WORLD_HHP_DOGS-dogMaxToShareWithFleas", 1.0,
	"total % of a dogs resource that can be taken by fleas. If fleas would take more then this amount, fleas consumption is normalized");


std::shared_ptr < ParameterLink<double>> HHPWorld::catParasiteInheritancePL =
Parameters::register_parameter("WORLD_HHP_INFECTION-parasiteInheritanceCat", 0.1,
	"percentage of a dogs fleas that migrate to an offspring");
std::shared_ptr < ParameterLink<double>> HHPWorld::dogParasiteInheritancePL =
Parameters::register_parameter("WORLD_HHP_INFECTION-parasiteInheritanceDog", 0.1,
	"percentage of a cats fleas that migrate to an offspring");

std::shared_ptr < ParameterLink<double>> HHPWorld::resourceInflowPL =
Parameters::register_parameter("WORLD_HHP-resourceInflow", 10.0,
	"how much resource does each location in the world have every update. Cats and dogs get their own resources. Resources are not maintained between updates");



std::shared_ptr < ParameterLink<double>> HHPWorld::Host::catLifeMinPL =
Parameters::register_parameter("WORLD_HHP_CATS-catLifeMin", 50.0,
	"cat lifespan minimum");
std::shared_ptr < ParameterLink<double>> HHPWorld::Host::catLifeMaxPL =
Parameters::register_parameter("WORLD_HHP_CATS-catLifeMax", 100.0,
	"cat lifespan maximum");
std::shared_ptr < ParameterLink<double>> HHPWorld::Host::dogLifeMinPL =
Parameters::register_parameter("WORLD_HHP_DOGS-dogLifeMin", 50.0,
	"dog lifespan minimum");
std::shared_ptr < ParameterLink<double>> HHPWorld::Host::dogLifeMaxPL =
Parameters::register_parameter("WORLD_HHP_DOGS-dogLifeMax", 100.0,
	"dog lifespan maximum");
std::shared_ptr < ParameterLink<double>> HHPWorld::Parasite::fleaLifeMinPL =
Parameters::register_parameter("WORLD_HHP_FLEAS-fleaLifeMin", 15.0,
	"flea lifespan minimum");
std::shared_ptr < ParameterLink<double>> HHPWorld::Parasite::fleaLifeMaxPL =
Parameters::register_parameter("WORLD_HHP_FLEAS-fleaLifeMax", 30.0,
	"flea lifespan maximum");

std::shared_ptr < ParameterLink<std::string>> HHPWorld::contactRateInSpeciesPL =
Parameters::register_parameter("WORLD_HHP_INFECTION-rateOfContactInSpecies", (std::string)"0X.1",
	"Rate per host in a location that contacts occur within a single host type.\n"
	"format is a list timeXvalue,timeXvalue,... where time is in updates");
std::shared_ptr < ParameterLink<std::string>> HHPWorld::contactRateAcrossSpeciesPL =
Parameters::register_parameter("WORLD_HHP_INFECTION-rateOfContactAcrossSpecies", (std::string)"0X.01",
	"Rate per host in a location that contacts occur without regard  to host type.\n"
	"format is a list timeXvalue,timeXvalue,... where time is in updates");

std::shared_ptr < ParameterLink<double>> HHPWorld::transferRatePL =
Parameters::register_parameter("WORLD_HHP_INFECTION-rateOfTransfer", .1,
	"when contact occurs, what % of each hosts parasites are transfered to the other. -1 will result in exactly 1");

std::shared_ptr < ParameterLink<int>> HHPWorld::cullParasitesToPL =
Parameters::register_parameter("WORLD_HHP_TUNING-cullParasitesTo", 20,
	//"Before parasites reproduce on a host, the number of parasites on that host is culled to this many.");
	"If a host has this many (or more) parasites, parasites will not reproduce on that host");

std::shared_ptr < ParameterLink<double>> HHPWorld::HostParasiteRelationshipPL =
Parameters::register_parameter("WORLD_HHP-ParasiteRelationship", -1.0,
	"What is the relationship between host and parasite? \n"
	"-1.0: (default) parasites remove all resource gained from host\n"
	" 0.0: 'parasites' do not steal resources from hosts (commensalism)\n"
	" 1.0: hosts gain additional resource when 'parasites' gain resource (mutualism)");

std::shared_ptr < ParameterLink<double>> HHPWorld::ParasitesStartOnCatsPL =
Parameters::register_parameter("WORLD_HHP_INFECTION-ParasitesStartOnCats", 1.0,
	"% of parasites that start on cats (as opposed to dogs)");


HHPWorld::HHPWorld(std::shared_ptr<ParametersTable> PT_)
	: AbstractWorld(PT_) {

	mutationEraseRate = mutationEraseRatePL->get(PT);

	reproductionThresholdCat = reproductionThresholdCatPL->get(PT);
	reproductionThresholdDog = reproductionThresholdDogPL->get(PT);
	reproductionThresholdFlea = reproductionThresholdFleaPL->get(PT);
	turnRateCat = turnRateCatPL->get(PT);
	turnRateDog = turnRateDogPL->get(PT);
	moveRateCat = moveRateCatPL->get(PT);
	moveRateDog = moveRateDogPL->get(PT);
	catFleaFeedAmt = catFleaFeedAmtPL->get(PT);
	dogFleaFeedAmt = dogFleaFeedAmtPL->get(PT);
	catMaxToShareWithFleas = catMaxToShareWithFleasPL->get(PT);
	dogMaxToShareWithFleas = dogMaxToShareWithFleasPL->get(PT);
	resourceInflow = resourceInflowPL->get(PT);

	catParasiteInheritance = catParasiteInheritancePL->get(PT);
	dogParasiteInheritance = dogParasiteInheritancePL->get(PT);

	convertTemoporalList((std::string)contactRateInSpeciesPL->get(PT), contactRateInSpeciesList, contactRateInSpeciesTimesList);
	convertTemoporalList((std::string)contactRateAcrossSpeciesPL->get(PT), contactRateAcrossSpeciesList, contactRateAcrossSpeciesTimesList);
	contactRateInSpecies = contactRateInSpeciesList[0];
	contactRateAcrossSpecies = contactRateAcrossSpeciesList[0];

	convertTemoporalList((std::string)mutationPointCatPL->get(PT), mutationPointCatList, mutationPointCatTimesList);
	convertTemoporalList((std::string)mutationSizeCatPL->get(PT), mutationSizeCatList, mutationSizeCatTimesList);
	convertTemoporalList((std::string)mutationPointDogPL->get(PT), mutationPointDogList, mutationPointDogTimesList);
	convertTemoporalList((std::string)mutationSizeDogPL->get(PT), mutationSizeDogList, mutationSizeDogTimesList);
	convertTemoporalList((std::string)mutationPointFleaPL->get(PT), mutationPointFleaList, mutationPointFleaTimesList);
	convertTemoporalList((std::string)mutationSizeFleaPL->get(PT), mutationSizeFleaList, mutationSizeFleaTimesList);
	mutationPointCat = mutationPointCatList[0];
	mutationSizeCat = mutationSizeCatList[0];
	mutationPointDog = mutationPointDogList[0];
	mutationSizeDog = mutationSizeDogList[0];
	mutationPointFlea = mutationPointFleaList[0];
	mutationSizeFlea = mutationSizeFleaList[0];

	transferRate = transferRatePL->get(PT);

	convertCSVListToVector(scoreListPL->get(PT), scoreList);

	cullParasitesTo = cullParasitesToPL->get(PT);

	worldX = worldXPL->get(PT);
	worldY = worldYPL->get(PT);
	worldWraps = worldWrapsPL->get(PT);
	std::cout << "HHPWorld constructor..." << std::endl << "  World Size " << worldX << ", " << worldY << std::endl;
	recordImageStep = recordImageStepPL->get(PT);
	recordWorldStateStep = recordWorldStateStepPL->get(PT);
	recordGenomesStep = recordGenomesStepPL->get(PT);

	HostParasiteRelationship = HostParasiteRelationshipPL->get(PT);

	// columns to be added to ave file
	popFileColumns.clear();
	//popFileColumns.push_back("value");
}

// create a flea and place on the provided host
// flea will be added to fleas
// genome will be randomized if initGenome = true (default)
void HHPWorld::createFlea(std::shared_ptr<Organism>& org, std::shared_ptr<Host>& host, bool initGenome) {
	// make a cat and place it in world
	auto newFlea = std::make_shared<Parasite>(org);
	//newFlea->bitstring = getBitString(startingKeyLengthFlea, false);
	fleas.push_back(newFlea);
	host->parasites.push_back(newFlea);
}


// create a Cat. cat will be added to cats and world.
// if x, y, direction are not provided, cat will be placed randomly in world
// genome will be randomized if initGenome = true (default)
void HHPWorld::createCat(std::shared_ptr<Organism>& org, int x, int y, int direction, bool initGenome) {
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
	//newCat->bitstring = getBitString(startingLockLengthCat, false);
	cats.push_back(newCat);
	world(newCat->x, newCat->y).hosts.push_back(newCat);
	world(newCat->x, newCat->y).catCount++;
}

// create a Dog. dog will be added to dogs and world.
// if x, y, direction are not provided, dog will be placed randomly in world
// genome will be randomized if initGenome = true (default)
void HHPWorld::createDog(std::shared_ptr<Organism>& org, int x, int y, int direction, bool initGenome) {
	//randomize genome
	//if (initGenome) {
	//	org->genomes["dog::"]->fillRandom();
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
	auto newDog = std::make_shared<Host>(org, HostTag::dogTag, x, y, direction);;
	//newDog->bitstring = getBitString(startingLockLengthDog, false);
	dogs.push_back(newDog);
	world(newDog->x, newDog->y).hosts.push_back(newDog);
	world(newDog->x, newDog->y).dogCount++;
}

// birth a flea given a parent and host
// flea will be placed in the provided hosts parasite vector and fleas
void HHPWorld::birthFlea(std::shared_ptr<Parasite>& parent, std::shared_ptr<Host>& host) {
	// make a new mabe offspring org from parent org
	auto newOrg = parent->org->makeMutatedOffspringFrom(parent->org);
	createFlea(newOrg, host, false);
	auto newFlea = fleas.back();
	newFlea->bitstring = parent->bitstring;
	mutateBitString(newFlea->bitstring,mutationPointFlea, mutationSizeFlea);

	newFlea->bitStringMatch = percentMatch(newFlea->bitstring, host->bitstring, scoreList);





	fleaBirths++;
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
	//std::cout << "  in birthCat :: update = " << Global::update << " new_org timeOfBrith = " << newOrg->timeOfBirth << std::endl;
	// place in world in same location at parent with random direction
	createCat(newOrg, x, y, direction, false);
	auto newCat = cats.back();
	newCat->bitstring = parent->bitstring;
	mutateBitString(newCat->bitstring, mutationPointCat, mutationSizeCat);
	jumpFleas(parent, newCat, catParasiteInheritance);

	catBirths++;
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
	createDog(newOrg, x, y, direction, false);
	auto newDog = dogs.back();
	newDog->bitstring = parent->bitstring;
	mutateBitString(newDog->bitstring, mutationPointDog, mutationSizeDog);
	jumpFleas(parent, newDog, dogParasiteInheritance);

	dogBirths++;
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
		std::cout << "    in HHPWorld::killParasite() :: parasite was not in provided parasite vector on provided host! exiting..." << std::endl;
		exit(1);
	}

	// remove from host
	host->parasites.erase(it);

	// find this parasite in the provided parasites list
	it = std::find(parasites.begin(), parasites.end(), parasite);
	if (it == parasites.end()) {
		std::cout << "    in HHPWorld::killParasite() :: parasite was not in provided parasites vector! exiting..." << std::endl;
		exit(1);
	}
	parasites.erase(it);
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
	
	// kill parasites on host

	//if (host->parasites.size() > 0)
	for (int i = host->parasites.size() - 1; i >= 0; i--) {
		killParasite(host->parasites[i],host,fleas,fleaKillList);
	}

	auto it = std::find(world(host->x, host->y).hosts.begin(), world(host->x, host->y).hosts.end(), host);
	if (it == world(host->x, host->y).hosts.end()) {
		std::cout << "    in HHPWorld::killHost() :: host was not in world location! exiting..." << std::endl;
		exit(1);
	}

	// remove host form world
	world(host->x, host->y).hosts.erase(it);

	if (host->tag == HostTag::catTag) {
		world(host->x, host->y).catCount--;
	}
	if (host->tag == HostTag::dogTag) {
		world(host->x, host->y).dogCount--;
	}

	// find this host in the provided hosts list
	it = std::find(hosts.begin(), hosts.end(), host);
	if (it == hosts.end()) {
		std::cout << "    in HHPWorld::killHost() :: host was not in provided hosts vector! exiting..." << std::endl;
		exit(1);
	}

	// remove from provided host list
	hosts.erase(it);
}

// kill a flea, see killParasite
void HHPWorld::killFlea(std::shared_ptr<Parasite>& flea, std::shared_ptr<Host>& host) {
	killParasite(flea, host, fleas, fleaKillList);
	fleaDeaths++;
}

// kill a cat, see killHost
void HHPWorld::killCat(std::shared_ptr<Host>& cat) {
	killHost(cat, cats, catKillList);
	catDeaths++;
}

// kill a dog, see killHost
void HHPWorld::killDog(std::shared_ptr<Host>& dog) {
	killHost(dog, dogs, dogKillList);
	dogDeaths++;
}

// setupPopulations is called from evaluate and is used to convert mabe
// groups to Hosts (cats, dogs) and Parasites (fleas)
void HHPWorld::setupPopulations(std::map<std::string, std::shared_ptr<Group>>& groups,
		int analyze, int visualize, int debug) {
	std::cout << "Starting with cat population size: " << groups["cat::"]->population.size() << std::endl;

	int initCatLockLength = initCatLockLengthPL->get(PT);
	std::string initCatLock = initCatLockPL->get(PT);
	int initDogLockLength = initDogLockLengthPL->get(PT);
	std::string initDogLock = initDogLockPL->get(PT);
	int initFleaKeyLength = initFleaKeyLengthPL->get(PT);
	std::string initFleaKey = initFleaKeyPL->get(PT);

	for (auto org : groups["cat::"]->population) {
		createCat(org);
		cats.back()->bitstring = getBitString(initCatLockLength, initCatLock);
	}
	std::cout << "Starting with dog population size: " << groups["dog::"]->population.size() << std::endl;
	for (auto org : groups["dog::"]->population) {
		createDog(org);
		dogs.back()->bitstring = getBitString(initDogLockLength, initDogLock);
	}
	std::cout << "Starting with flea population size: " << groups["flea::"]->population.size() << std::endl;
	for (auto org : groups["flea::"]->population) {
		// this will distribute parasites equaly to cat and dog populations
		if (Random::P(ParasitesStartOnCatsPL->get(PT))) {
			int orgID = Random::getIndex(cats.size());
			createFlea(org, cats[orgID]);
			fleas.back()->bitstring = getBitString(initFleaKeyLength, initFleaKey);
			cats[orgID]->parasites.back()->bitStringMatch = percentMatch(cats[orgID]->parasites.back()->bitstring, cats[orgID]->bitstring, scoreList);
		}
		else {
			int orgID = Random::getIndex(dogs.size());
			createFlea(org, dogs[orgID]);
			fleas.back()->bitstring = getBitString(initFleaKeyLength, initFleaKey);
			dogs[orgID]->parasites.back()->bitStringMatch = percentMatch(dogs[orgID]->parasites.back()->bitstring, dogs[orgID]->bitstring, scoreList);
		}
	}

	groups["cat::"]->archivist->save_new_orgs_ = true;
	groups["dog::"]->archivist->save_new_orgs_ = true;
	groups["flea::"]->archivist->save_new_orgs_ = true;
}

// given a host group (cats or dogs) 
void HHPWorld::updateHosts(std::vector < std::shared_ptr<Host>> hostList) {
	std::vector < std::shared_ptr<Host>> localHostKillList;
	std::vector < std::shared_ptr<Host>> localHostParentList;

	double parasiteInflow = 0;

	for (int hostIndex = 0; hostIndex < hostList.size(); hostIndex++) {
		auto h = hostList[hostIndex];
		bool isCat = hostList[hostIndex]->tag == HostTag::catTag;

		// Random host death or livespan over.
		if (h->timeOfDeath <= Global::update) {
			localHostKillList.push_back(h); // don't kill them yet... it'll mess up the interation!
		}

		else {

			std::shuffle(h->parasites.begin(), h->parasites.end(), Random::getCommonGenerator());

			std::vector < std::pair<std::shared_ptr<Parasite>, std::shared_ptr<Host>>> localParasiteKillList;
			std::vector < std::pair<std::shared_ptr<Parasite>, std::shared_ptr<Host>>> localParasiteParentList;

			int hostCountHere = (isCat) ? world(h->x, h->y).catCount : world(h->x, h->y).dogCount;
			double hostInflow = resourceInflow / hostCountHere;
			double theft = 0;

			double fleaFeedAmt = (isCat) ? catFleaFeedAmt : dogFleaFeedAmt;
			double maxToShareWithFleas = (isCat) ? catMaxToShareWithFleas : dogMaxToShareWithFleas;

			//double lostResources = h->resource * resourcesLostPercentage;

			// which parasites die from old age
			for (int i = 0; i < h->parasites.size(); i++) {
				if (h->parasites[i]->timeOfDeath < Global::update) {
					//std::cout << "old: " << h->parasites[i]->org->ID << std::endl;
					localParasiteKillList.push_back({ h->parasites[i],h });
				}
			}

			// get rid of old fleas now!
			for (auto p : localParasiteKillList) {
				//std::cout << " -F ";
				killFlea(p.first, p.second);
			}


			bool cullMethod = false;
			// cull method culls population down to cullParasitesTo
			// if not in use, then parasites will not reporduce if # would exceed(see below)
			if (cullMethod) {
				for (int i = h->parasites.size() - 1; i > cullParasitesTo; i--) {
					killFlea(h->parasites[i], h);
				}
			}


			std::vector<double> parasiteShares(h->parasites.size());
			double totalParasitesShares = 0;

			h->bitStringMatch = 0;

			for (int i = 0; i < h->parasites.size(); i++) {
				// How many does each parasite get?
				
				// move to birth (and migration and setup)
				//h->parasites[i]->bitStringMatch = percentMatch(h->parasites[i]->bitstring, h->bitstring, scoreList);
				//

				h->bitStringMatch += h->parasites[i]->bitStringMatch;
				parasiteShares[i] = fleaFeedAmt * h->parasites[i]->bitStringMatch;
				totalParasitesShares += parasiteShares[i];
			}
			if (h->parasites.size() > 0) {
				h->bitStringMatch /= h->parasites.size();
			}
			else {
				h->bitStringMatch = -1;
			}
			if (totalParasitesShares > maxToShareWithFleas) {
				double correctionFactor = maxToShareWithFleas / totalParasitesShares;
				for (int i = 0; i < h->parasites.size(); i++) {
					parasiteShares[i] *= correctionFactor;
				}
			}

			for (int i = 0; i < h->parasites.size(); i++) {
				// Parasites get resource... host loses resource
				parasiteInflow = parasiteShares[i] * hostInflow;
				h->parasites[i]->resource += parasiteInflow;
				h->parasites[i]->collectedResource = parasiteInflow;
				theft += parasiteInflow;

				if (cullMethod) {
					// can parasite reproduce ?
					if (h->parasites[i]->resource > reproductionThresholdFlea) {
						localParasiteParentList.push_back({ h->parasites[i],h });
						h->parasites[i]->resource = 0.0;
					}
				}
			}
			//std::cout << isCat << "  hostCountHere: " << hostCountHere << "  parasites: " << h->parasites.size() << "  totalParasitesShares: " << totalParasitesShares << std::endl;
			//std::cout << "hostInflow: " << hostInflow << "  theft: " << theft << std::endl;

			//std::cout << "host resource before: " << h->resource;
			h->resource += hostInflow + (theft * HostParasiteRelationship);
			h->collectedResource = hostInflow - theft;
			h->theft = theft;

			//std::cout << "  parasites count: " << h->parasites.size() << "  hostInflow: " << hostInflow << "  theft: " << theft << " host resource after: " << h->resource << std::endl;
			if(h->resource < 0.1){
				std::cout << h->org->ID << " STARVED with " << h->resource << " resources." << std::endl;
				localHostKillList.push_back(h);
			}
			else { // if host did starve
				if (cullMethod) {
					// produce offspring fleas now
					for (auto p : localParasiteParentList) {
						//std::cout << " +F ";
						birthFlea(p.first, p.second);
					}
				}

				// Check reproduction
				double reproductionCost = isCat ? reproductionThresholdCat : reproductionThresholdDog;

				// If we have enough resources, reproduce
				if (h->resource > reproductionCost) {
					localHostParentList.push_back(h);
					h->resource = 0.0;
				}


				// Move hosts
				double turnRate = isCat ? turnRateCat : turnRateDog;
				double moveRate = isCat ? moveRateCat : moveRateDog;

				//std::cout << "turnRate: " << turnRate << "  moveRate: " << moveRate << std::endl;
				//std::cout << "    direction: " << h->direction << "  " << h->x << ", " << h->y << std::endl;
				if (Random::P(turnRate)) { // with probability turnRate turn left or right 45 degrees
					h->direction = loopMod(h->direction + (Random::getIndex(2) * 2 - 1), 8); // i.e. direction +/- 1
				}
				if (Random::P(moveRate)) { // with probability moveRate move forward
					moveInWorld(h);
				}
				//std::cout << "    direction: " << h->direction << "  " << h->x << ", " << h->y << std::endl;

				if (!cullMethod) {
					for (int i = 0; i < h->parasites.size(); i++) {
						if (h->parasites.size() + localParasiteParentList.size() >= cullParasitesTo) {
							break;
						}
						if (h->parasites[i]->resource > reproductionThresholdFlea) {
							localParasiteParentList.push_back({ h->parasites[i],h });
							h->parasites[i]->resource = 0.0;
						}
					}
					// produce offspring fleas now
					for (auto p : localParasiteParentList) {
						//std::cout << " +F ";
						birthFlea(p.first, p.second);
					}
				}
			}
		}
	}
	// Birth some babies
	for(auto h : localHostParentList ){
		if(h->tag == HostTag::catTag){
			//std::cout << " +C ";
			birthCat(h);
		} else {
			//std::cout << " +D ";
			birthDog(h);
		}
	}

	// now kill the ones that died.
	//std::cout << "Killing: ";
	int killed_cats_count=0;
	int killed_dogs_count=0;

	for (auto h : localHostKillList) {
		if (h->tag == HostTag::catTag) {
			//std::cout << " -C ";
			killCat(h); // kill a cat, and it's parasites
			killed_cats_count++;
		}
		else {
			//std::cout << " -D ";
			killDog(h); // kill a dog, and it's parasites
			killed_dogs_count++;
		}
	}
	//std::cout << std::endl << killed_cats_count << " cats and " << killed_dogs_count << " dogs." << std::endl;
}

// jump flea from h1 to h2 (if h1 has fleas)
// percent determins what percent of h1s fleas jump to h2. if < 0 (default) one will jump.
void HHPWorld::jumpFleas(std::shared_ptr<Host> h1, std::shared_ptr<Host> h2, double moveRate) {
	int numberToJumpFrom1;
	int numberToJumpFrom2;

	if (moveRate < 0 && h1->parasites.size() > 0) { // if numberToJump < 0 then default to 1
		numberToJumpFrom1 = 1;
	}
	else {
		numberToJumpFrom1 = Random::getBinomial(h1->parasites.size(), moveRate);
	}
	if (moveRate < 0 && h2->parasites.size() > 0) { // if numberToJump < 0 then default to 1
		numberToJumpFrom2 = 1;
	}
	else {
		numberToJumpFrom2 = Random::getBinomial(h2->parasites.size(), moveRate);
	}

	fleaJumps += numberToJumpFrom1 + numberToJumpFrom2;
	
	std::vector<std::shared_ptr<Parasite>> parasiteBank;
	int jumperIndex;
	// get some parasites form h1 and place in parasiteBank
	for (int i = 0; i < numberToJumpFrom1; i++) {
		jumperIndex = Random::getIndex(h1->parasites.size()); // get an index for a parasite on doner
		
		// change parasite bitMatch to new hosts value
		h1->parasites[jumperIndex]->bitStringMatch = percentMatch(h1->parasites[jumperIndex]->bitstring, h2->bitstring, scoreList);

		parasiteBank.push_back(h1->parasites[jumperIndex]); // jump parasite to the reciver
		h1->parasites.erase(h1->parasites.begin() + jumperIndex); // remove parasite from doner
	}
	// move some parasites form h2 to h1
	for (int i = 0; i < numberToJumpFrom2; i++) {
		jumperIndex = Random::getIndex(h2->parasites.size()); // get an index for a parasite on doner

		// change parasite bitMatch to new hosts value
		h2->parasites[jumperIndex]->bitStringMatch = percentMatch(h2->parasites[jumperIndex]->bitstring, h1->bitstring, scoreList);

		h1->parasites.push_back(h2->parasites[jumperIndex]); // jump parasite to the reciver
		h2->parasites.erase(h2->parasites.begin() + jumperIndex); // remove parasite from doner
	}
	// place parasites in bank into h2s parasite list
	h2->parasites.insert(h2->parasites.end(), parasiteBank.begin(), parasiteBank.end());
}

void HHPWorld::migrateParasites(std::vector<std::shared_ptr<Host>> & hosts, double localContactRate) {
	if (hosts.size() > 1) {
		int contacts = Random::getBinomial(hosts.size(), localContactRate);
		for (int i = 0; i < contacts; i++) {
			std::shared_ptr<Host> h1 = hosts[Random::getIndex(hosts.size())]; // doner host
			std::shared_ptr<Host> h2;
			do {
				h2 = hosts[Random::getIndex(hosts.size())]; // reciver host
			} while (h1 == h2); // keep picking until doner != reciver
			jumpFleas(h1, h2, transferRate);
			if (h1->tag != h2->tag) {
				fleaJumpsAcross++;
			}
		}
	}
}


void HHPWorld::evaluate(std::map<std::string, std::shared_ptr<Group>>& groups,
		int analyze, int visualize, int debug) {
	
	//tests();

	// initalize world
	world.reset(worldX, worldY);
	// convert mabe populatoins to cats, dogs, and fleas


	setupPopulations(groups, analyze, visualize, debug);

	std::cout << "  HHPWorld :: starting evaluation" << std::endl;
	std::cout << "    setup done" << std::endl;

	std::cout << "      fleas count: " << fleas.size() << std::endl << std::endl;
	std::cout << "      cat count: " << cats.size() << std::endl;
	std::cout << "        ave_fleas(cats): " << ave_fleas(cats) << std::endl << std::endl;
	std::cout << "      dog count: " << dogs.size() << std::endl;
	std::cout << "        ave_fleas(dogs): " << ave_fleas(dogs) << std::endl << std::endl;



	int contactRateInSpeciesCounter = 0;
	int contactRateAcrossSpeciesCounter = 0;

	int mutationPointCatCounter = 0;
	int mutationSizeCatCounter = 0;
	int mutationPointDogCounter = 0;
	int mutationSizeDogCounter = 0;
	int mutationPointFleaCounter = 0;
	int mutationSizeFleaCounter = 0;

	// run the evaluation until time runs out...
	do {

		advanceTemporalList(contactRateInSpeciesCounter, contactRateInSpecies, contactRateInSpeciesList, contactRateInSpeciesTimesList);
		advanceTemporalList(contactRateAcrossSpeciesCounter, contactRateAcrossSpecies, contactRateAcrossSpeciesList, contactRateAcrossSpeciesTimesList);

		advanceTemporalList(mutationPointCatCounter, mutationPointCat, mutationPointCatList, mutationPointCatTimesList);
		advanceTemporalList(mutationSizeCatCounter, mutationSizeCat, mutationSizeCatList, mutationSizeCatTimesList);
		advanceTemporalList(mutationPointDogCounter, mutationPointDog, mutationPointDogList, mutationPointDogTimesList);
		advanceTemporalList(mutationSizeDogCounter, mutationSizeDog, mutationSizeDogList, mutationSizeDogTimesList);
		advanceTemporalList(mutationPointFleaCounter, mutationPointFlea, mutationPointFleaList, mutationPointFleaTimesList);
		advanceTemporalList(mutationSizeFleaCounter, mutationSizeFlea, mutationSizeFleaList, mutationSizeFleaTimesList);

		catBirths = 0;
		dogBirths = 0;
		fleaBirths = 0;
		catDeaths = 0;
		dogDeaths = 0;
		fleaDeaths = 0;
		fleaJumps = 0;
		fleaJumpsAcross = 0;

		// update all hosts (death, resource, movement)
		updateHosts(cats);
		updateHosts(dogs);
		fleasInherited = fleaJumps;
		fleaJumps = 0;

		// parasite migration
		for (int y = 0; y < worldY; y++) { // for all locations in the world
			for (int x = 0; x < worldX; x++) {
				std::vector<std::shared_ptr<Host>> catHosts;
				std::vector<std::shared_ptr<Host>> dogHosts;
				for (auto h : world(x, y).hosts) {
					if (h->tag == HostTag::catTag) {
						catHosts.push_back(h);
					}
					else {
						dogHosts.push_back(h);
					}
				}
				migrateParasites(catHosts, contactRateInSpecies);
				migrateParasites(dogHosts, contactRateInSpecies);
				migrateParasites(world(x, y).hosts, contactRateAcrossSpecies);
			}
		}



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

		std::cout << "Average fleas per cat: " << ave_fleas(cats) << std::endl;
		std::cout << "Average fleas per dog: " << ave_fleas(dogs) << std::endl;

		if (0) {
			std::cout << "\ncatCounts:" << std::endl;
			for (int y = 0; y < worldY; y++) {
				for (int x = 0; x < worldX; x++) {
					if (world(x, y).catCount == 0) {
						std::cout << " " << "  ";
					}
					else {
						std::cout << world(x, y).catCount << "  ";
					}
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;

			std::cout << "\ndogCounts:" << std::endl;
			for (int y = 0; y < worldY; y++) {
				for (int x = 0; x < worldX; x++) {
					if (world(x, y).dogCount == 0) {
						std::cout << " " << "  ";
					}
					else {
						std::cout << world(x, y).dogCount << "  ";
					}
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}



		// save image of world
		// this calls saveWorldImage which is currently written for MultiCellWorld
		if (recordImageStep > 0 && Global::update % recordImageStep == 0) {
			//saveWorldImage();
		}

		// save some world details to a csv file
		if (recordWorldStateStep > 0 && Global::update % recordWorldStateStep == 0) {

			std::string headerString = "update,cats,dogs,fleas,FpC,FpD,catLockAveSize,dogLockAveSize,";
			headerString += "fleaKeyAveSize,fleaKeyAveSizeOnCats,fleaKeyAveSizeOnDogs,";
			headerString += "catBirths,dogBirths,fleaBirths,catDeaths,dogDeaths,fleaDeaths,fleaJumps,fleaJumpsAcross,fleasInherited,";
			headerString += "catCollectedResource,fleaOnCatCollectedResource,catTheft,";
			headerString += "infectedCatsRate,";
			headerString += "bitMatchCat,";
			headerString += "dogCollectedResource,fleaOnDogCollectedResource,dogTheft,";
			headerString += "infectedDogsRate,";
			headerString += "bitMatchDog,";
			headerString += "fleaCollectedResource";


			std::string dataString = std::to_string(Global::update) + ",";
			dataString += std::to_string(cats.size()) + ",";
			dataString += std::to_string(dogs.size()) + ",";
			dataString += std::to_string(fleas.size()) + ",";
			dataString += std::to_string(ave_fleas(cats)) + ",";
			dataString += std::to_string(ave_fleas(dogs)) + ",";

			double fleaKeyAveSizeOnCats = 0;
			double fleaCountCats = 0;
			double fleaKeyAveSizeOnDogs = 0;
			double fleaCountDogs = 0;

			double catCollectedResource = 0;
			double dogCollectedResource = 0;
			double fleaOnCatCollectedResource = 0;
			double fleaOnDogCollectedResource = 0;
			double catTheft = 0;
			double dogTheft = 0;

			double bitMatchCat = 0;
			double infectedCats = 0;

			double bitMatchDog = 0;
			double infectedDogs = 0;

			if (cats.size() > 0) {
				double catLockAveSize = 0;
				for (auto c : cats) {
					catLockAveSize += c->bitstring.size();
					for (auto p : c->parasites) {
						fleaKeyAveSizeOnCats += p->bitstring.size();
						fleaCountCats++;
						fleaOnCatCollectedResource += p->collectedResource;
					}
					catCollectedResource += c->collectedResource;
					catTheft += c->theft;
					if (c->parasites.size() > 0) {
						bitMatchCat += c->bitStringMatch;
						infectedCats++;
					}
				}
				dataString += std::to_string(catLockAveSize / cats.size()) + ",";
			}
			else {
				dataString += "-1,";
			}
			
			if (dogs.size() > 0) {
				double dogLockAveSize = 0;
				for (auto d : dogs) {
					dogLockAveSize += d->bitstring.size();
					for (auto p : d->parasites) {
						fleaKeyAveSizeOnDogs += p->bitstring.size();
						fleaCountDogs++;
						fleaOnDogCollectedResource += p->collectedResource;
					}
					dogCollectedResource += d->collectedResource;
					dogTheft += d->theft;
					if (d->parasites.size() > 0) {
						bitMatchDog += d->bitStringMatch;
						infectedDogs++;
					}
				}
				dataString += std::to_string(dogLockAveSize / dogs.size()) + ",";
			}
			else {
				dataString += "-1,";
			}			
			
			
			if (fleas.size() > 0) {
				double fleasKeyAveSize = 0;
				for (auto f : fleas) {
					fleasKeyAveSize += f->bitstring.size();
				}
				dataString += std::to_string(fleasKeyAveSize / fleas.size())+",";
			}
			else {
				dataString += "-1,";
			}


			if (fleaCountCats > 0) {
				dataString += std::to_string(fleaKeyAveSizeOnCats / fleaCountCats) + ",";
			}
			else {
				dataString += "-1,";
			}
			if (fleaCountDogs > 0) {
				dataString += std::to_string(fleaKeyAveSizeOnDogs / fleaCountDogs) + ",";
			}
			else {
				dataString += "-1,";
			}
			
			dataString += std::to_string(catBirths) + ",";
			dataString += std::to_string(dogBirths) + ",";
			dataString += std::to_string(fleaBirths) + ",";
			dataString += std::to_string(catDeaths) + ",";
			dataString += std::to_string(dogDeaths) + ",";
			dataString += std::to_string(fleaDeaths) + ",";
			dataString += std::to_string(fleaJumps) + ",";
			dataString += std::to_string(fleaJumpsAcross) + ",";
			dataString += std::to_string(fleasInherited) + ",";


			if (cats.size() > 0) {
				double cs = double(cats.size());
				dataString += std::to_string(catCollectedResource / cs) + ",";
				dataString += std::to_string(fleaOnCatCollectedResource / cs) + ",";
				dataString += std::to_string(catTheft / cs) + ",";
				dataString += std::to_string(infectedCats / cs) + ",";
			}
			else {
				dataString += "-1,-1,-1,-1,";
			}


			if (infectedCats > 0) {
				dataString += std::to_string(bitMatchCat / infectedCats) + ",";
			}
			else {
				dataString += "-1,";
			}


			if (dogs.size() > 0) {
				double ds = double(dogs.size());
				dataString += std::to_string(dogCollectedResource / ds) + ",";
				dataString += std::to_string(fleaOnDogCollectedResource / ds) + ",";
				dataString += std::to_string(dogTheft / ds) + ",";
				dataString += std::to_string(infectedDogs / ds) + ",";
			}
			else {
				dataString += "-1,-1,-1,-1,";
			}


			if (infectedDogs > 0) {
				dataString += std::to_string(bitMatchDog / infectedDogs) + ",";
			}
			else {
				dataString += "-1,";
			}


			if (fleas.size() > 0) {
				dataString += std::to_string((fleaOnCatCollectedResource + fleaOnDogCollectedResource) / fleas.size());
			}
			else {
				dataString += "-1";
			}

			FileManager::writeToFile("HHP_Report.csv", dataString, headerString);
		}
		
		if (recordGenomesStep > 0 && Global::update % recordGenomesStep == 0) {
			std::string headerString = "ID,genomeSize,genome";
			std::string dataString;
			dataString = "";
			for (auto& o : cats) {
				dataString += std::to_string(o->org->ID) + ",";
				dataString += std::to_string(o->bitstring.size()) + ",";
				dataString += serializeGenome(o->bitstring) + "\n";
				for (auto& p : o->parasites) {
					p->hostTag = HostTag::catTag;
					p->hostID = o->org->ID;
				}
			}
			FileManager::writeToFile("HHP_cats_" + std::to_string(Global::update) + ".csv", dataString, headerString);
			dataString = "";
			for (auto& o : dogs) {
				dataString += std::to_string(o->org->ID) + ",";
				dataString += std::to_string(o->bitstring.size()) + ",";
				dataString += serializeGenome(o->bitstring) + "\n";
				for (auto& p : o->parasites) {
					p->hostTag = HostTag::dogTag;
					p->hostID = o->org->ID;
				}
			}
			FileManager::writeToFile("HHP_dogs_" + std::to_string(Global::update) + ".csv", dataString, headerString);
			headerString = "ID,genomeSize,genome,hostID,hostType,collectedResource,bitStringMatch";
			dataString = "";
			for (auto& o : fleas) {
				dataString += std::to_string(o->org->ID) + ",";
				dataString += std::to_string(o->bitstring.size()) + ",";
				dataString += serializeGenome(o->bitstring) + ",";
				dataString += std::to_string(o->hostID) + ",";
				if (o->hostTag == HostTag::catTag) {
					dataString += "0,";
				}
				else {
					dataString += "1,";
				}
				dataString += std::to_string(o->collectedResource) + ",";
				dataString += std::to_string(o->bitStringMatch) + "\n";
			}
			FileManager::writeToFile("HHP_fleas_" + std::to_string(Global::update) + ".csv", dataString, headerString);
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

		// advance time
		Global::update++;

		// keep going until the archivist say we are done.
	} while (!groups["cat::"]->archivist->finished_ && !groups["dog::"]->archivist->finished_ && !groups["flea::"]->archivist->finished_ && (dogs.size()+cats.size()>0));
	std::cout << "finished run!" << std::endl;
}

std::unordered_map<std::string, std::unordered_set<std::string>>
HHPWorld::requiredGroups() {
	return { {"cat::",{}}, {"dog::",{}}, {"flea::",{}} };
	// this world needs cats, dogs and fleas, each with a genome with the same name...
}


double
HHPWorld::ave_fleas(std::vector<std::shared_ptr<Host>> hosts){
	if (hosts.size() == 0) {
		return 0;
	}
	else {
		double sum = 0;
		for (int i = 0; i < hosts.size(); ++i) {
			sum += hosts[i]->parasites.size();
		}
		return sum / hosts.size();
	}
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
