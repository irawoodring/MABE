

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

HHPWorld::HHPWorld(std::shared_ptr<ParametersTable> PT_)
	: AbstractWorld(PT_) {


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
void HHPWorld::createCat(std::shared_ptr<Organism>& org, int x, int y, int direction, bool initGenome) {
	//randomize genome
	if (initGenome) {
		org->genomes["cat::"]->fillRandom();
	}
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
	newCat->bitstring = std::vector<bool>(Random::getInt(1,10));
	for(int i=0; i<newCat->bitstring.size(); ++i){
		newCat->bitstring[i] = Random::getInt(1);
	}
	cats.push_back(newCat);
	world(newCat->x, newCat->y).hosts.push_back(newCat);
}

// create a Dog. dog will be added to dogs and world.
// if x, y, direction are not provided, dog will be placed randomly in world
// genome will be randomized if initGenome = true (default)
void HHPWorld::createDog(std::shared_ptr<Organism>& org, int x, int y, int direction, bool initGenome) {
	//randomize genome
	if (initGenome) {
		org->genomes["dog::"]->fillRandom();
	}
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
	newDog->bitstring = std::vector<bool>(Random::getInt(1,10));
	for(int i=0; i<newDog->bitstring.size(); ++i){
		newDog->bitstring[i] = Random::getInt(1);
	}
	dogs.push_back(newDog);
	world(newDog->x, newDog->y).hosts.push_back(newDog);
}

// create a flea and place on the provided host
// flea will be added to fleas
// genome will be randomized if initGenome = true (default)
void HHPWorld::createFlea(std::shared_ptr<Organism>& org, std::shared_ptr<Host>& host, bool initGenome) {
	//randomize genome
	if (initGenome) {
		org->genomes["flea::"]->fillRandom();
	}
	// make a cat and place this in world
	auto newFlea = std::make_shared<Parasite>(org);
	newFlea->bitstring = std::vector<bool>(Random::getInt(1,10));
	for(int i=0; i<newFlea->bitstring.size(); ++i){
		newFlea->bitstring[i] = Random::getInt(1);
	}
	fleas.push_back(newFlea);
	host->parasites.push_back(newFlea);
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
	createCat(newOrg, x, y, direction, false);
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
}

// birth a flea given a parent and host
// flea will be placed in the provided hosts parasite vector and fleas
void HHPWorld::birthFlea(std::shared_ptr<Parasite>& parent, std::shared_ptr<Host>& host) {
	// make a new mabe offspring org from parent org
	auto newOrg = parent->org->makeMutatedOffspringFrom(parent->org);
	createFlea(newOrg, host, false);
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

	// kill parasites on host
	for (int i = 0; i < host->parasites.size(); i++) {
		killParasite(host->parasites[i],host,fleas,fleaKillList);
	}
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

	std::vector < std::shared_ptr<Host>> localKillList;

	for (int hostIndex = 0; hostIndex < hostList.size(); hostIndex++) {
		auto h = hostList[hostIndex];

		// kill with random chace 5% - just to show how death works
		if (Random::P(.05)) {
			localKillList.push_back(h); // don't kill them yet... it'll mess up the interation!
		}
		else {
			h->resource += 1; // eat something (you're all skin and bones!)
			for (auto p : h->parasites) {
				p->resource += (h->resource * .5) / h->parasites.size(); // parasites get 1/2 hosts food (less if there are more parasites...)
			}

			double turnRate = .1;
			double moveRate = .5;
			if (Random::P(turnRate)) { // with probability turnRate turn left of right 45 degrees
				h->direction += loopMod((h->direction + Random::getIndex(2) * 2) - 1, 8); // i.e. direction +/- 1
			}
			if (Random::P(moveRate)) { // with probability moveRate move forward
				moveInWorld(h);
			}
		}
	}

	// now kill the ones that died.
	for (auto h : localKillList) {
		if (h->tag == HostTag::catTag) {
			//std::cout << "   cat" << std::endl;
			killCat(h); // kill a cat, and it's parasites
		}
		else {
			//std::cout << "   dog" << std::endl;
			killDog(h); // kill a dog, and it's parasites
		}
	}
}

void HHPWorld::jumpFlea(std::shared_ptr<Host> h1, std::shared_ptr<Host> h2) { // jump flea from h1 to h2 (if h1 has fleas)
	if (h1->parasites.size() > 0) { // if doner has parasites
		//int jumperIndex = Random::getIndex(h1->parasites.size()); // get an index for a parasite on doner
		//h2->parasites.push_back(h1->parasites[jumperIndex]); // jump parasite to the reciver
		//h1->parasites.erase(h1->parasites.begin() + jumperIndex); // remove parasite from doner

		for(auto i=0; i<h1->parasites.size(); ++i){
			if(infect(h1->parasites[i]->bitstring, h2->bitstring, .5)){
				std::cout << "********** INFECTION! ***********" << std::endl;
				h1->show_infection();
				h1->parasites[i]->show_infection();
				h2->show_infection();
				std::cout << "*********************************" << std::endl;
				h2->parasites.push_back(h1->parasites[i]);
				h1->parasites.erase(h1->parasites.begin() + i);
			} else {
				std::cout << "*** INFECTION FAILED. ***" << std::endl;
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
					std::cout << "JUMPING " << h1->org->ID << " AND " << h2->org->ID << std::endl;
					jumpFlea(h1, h2);
				}
			}
		}

		// testing the setup....

		if (cats.size() > 0) {
			killCat(cats[0]);
		}

		if (dogs.size() > 0) {
			killDog(dogs[0]);
		}

		//for(int i=0; i<dogs.size(); ++i){
		//	std::cout << "Dog " << i << " now has " << dogs[i]->parasites.size() << " fleas." << std::endl;
		//}

		if (dogs.size() > 0) {
			birthDog(dogs.back(), Global::update % worldX, Global::update % worldY);
		//	birthDog(dogs.back(), 0, Global::update % worldY);
		//	birthDog(dogs.back(), 0, Global::update % worldY);
		}
		if (cats.size() > 0) {
			birthCat(cats.back(), Global::update % worldX, 0, 7);
		//	birthCat(cats.back(), Global::update % worldX, 0, 7);
		//	birthCat(cats.back(), Global::update % worldX, 0, 7);
		}

		if (fleas.size() > 0) {
			if (cats.size() > 0) {
				birthFlea(fleas.back(), cats[Random::getIndex(cats.size())]);
		//		birthFlea(fleas.back(), cats[Random::getIndex(cats.size())]);
		//		birthFlea(fleas.back(), cats[Random::getIndex(cats.size())]);
		//		birthFlea(fleas.back(), cats[Random::getIndex(cats.size())]);
		//		birthFlea(fleas.back(), cats[Random::getIndex(cats.size())]);
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
		

		// advance time
		Global::update++;

		// keep going until the archivist say we are done.
	} while (!groups["cat::"]->archivist->finished_ && !groups["dog::"]->archivist->finished_ && !groups["flea::"]->archivist->finished_);
	std::cout << "finished run!" << std::endl;
}

std::unordered_map<std::string, std::unordered_set<std::string>>
HHPWorld::requiredGroups() {
	return { {"cat::",{"G:cat::"}}, {"dog::",{"G:dog::"}}, {"flea::",{"G:flea::"}} };
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
