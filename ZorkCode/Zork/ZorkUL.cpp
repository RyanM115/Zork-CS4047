#include <iostream>

using namespace std;
#include "ZorkUL.h"

int main(int argc, char argv[]) {
	ZorkUL temp;
	temp.play();
	return 0;
}

ZorkUL::ZorkUL() {
	createRooms();
}

void ZorkUL::createRooms()  {
    Room *a, *b, *c, *d, *e, *e1, *f, *g, *h, *i, *j, *k, *l, *m, *o;

    a = new Room("Hallway");
    b = new Room("Bathroom");
        b->addItem(new Item("Unknown Pills", 3, 33));
    c = new Room("Sitting Room");
        c->addItem(new Item("TV Remote", 1, 22));
        c->addItem(new Item("Glass of Wine", 3, 33));
        c->addItem(new Item("Empty Glass", 3, 33));
    d = new Room("Front Door");
    e = new Room("Office");
        e->addItem(new Item("Pen", 1, 10));
    e1 = new Room("Unknown");
    f = new Room("Kitchen");
        b->addItem(new Item("Knife", 4, 33));
    g = new Room("Utility");
        g->addItem(new Item("Screwdriver", 3, 33));
    h = new Room("Garden");
        h->addItem(new Item("Glass of Wine", 3, 33));
        h->addItem(new Item("Empty Glass", 3, 33));
        h->addItem(new Item("Empty Glass", 3, 33));
    i = new Room("Driveway");

    j = new Room("Upstairs Hallway");
    k = new Room("Bedroom");
    l = new Room("Bathroom");
    m = new Room("Master Bedroom");
    o = new Room("Shed");
        o->addItem(new Item("Shovel", 10, 33));
        o->addItem(new Item("Axe", 10, 33));

//             (N, E, S, W)
    a->setExits(f, b, d, c);
    b->setExits(g, NULL, NULL, a);
    c->setExits(h, a, NULL, NULL);
    d->setExits(a, e, i, NULL);
    e->setExits(NULL, e1, NULL, d);
    e1->setExits(NULL, NULL, NULL, e);
    f->setExits(NULL, g, a, h);
    g->setExits(NULL, NULL, b, f);
    h->setExits(o, f, c, NULL);
    i->setExits(d, NULL, NULL, NULL);

    j->setExits(k, l, m, NULL);
    k->setExits(NULL, NULL, j, NULL);
    l->setExits(NULL, NULL, NULL, j);
    m->setExits(NULL, NULL, NULL, j);
    o->setExits(NULL, NULL, h, NULL);

        currentRoom = i;
}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
	printWelcome();

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the ZorkUL game is over.

	bool finished = false;
	while (!finished) {
		// Create pointer to command and give it a command.
		Command* command = parser.getCommand();
		// Pass dereferenced command and check for end of game.
		finished = processCommand(*command);
		// Free the memory allocated by "parser.getCommand()"
		//   with ("return new Command(...)")
		delete command;
	}
	cout << endl;
	cout << "end" << endl;
}

void ZorkUL::printWelcome() {
    cout << "Welcome to the simulation agent 47. Your objectives are as follows:"<< endl;
    cout << "Find the Target and Find the Package."<< endl;
    cout << "The target is said to be wandering aound the party whilst"<< endl;
    cout << "the package is hidden somewhere in the house."<< endl;
    cout << "You could not bring weapons into the party so you might want to improvise."<< endl;
    cout << "When the misssion is complete, come back outside."<< endl;
    cout << "Good Luck"<< endl;
    cout << "'info' for help"<< endl;
	cout << endl;
	cout << currentRoom->longDescription() << endl;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool ZorkUL::processCommand(Command command) {
	if (command.isUnknown()) {
		cout << "invalid input"<< endl;
		return false;
	}

	string commandWord = command.getCommandWord();
	if (commandWord.compare("info") == 0)
		printHelp();

	else if (commandWord.compare("map") == 0)
		{
        cout << "       [Shed] " << endl;
        cout << "         | " << endl;
        cout << "         | " << endl;
        cout << "      [Garden] ---- [Kitchen] --- [Utility]                            [Bedroom] " << endl;
        cout << "         |              |             |                                    | " << endl;
        cout << "         |              |             |                                    | " << endl;
        cout << "[Sitting Room] ---- [Hallway] --- [Bathroom]                      [Upstairs Hallway] --- [Bathroom] " << endl;
        cout << "                        |                                                  | " << endl;
        cout << "                        |                                                  | " << endl;
        cout << "                  [Front Door] ----- [Office] --- [Unknown]                  ---- [Master Bedroom] " << endl;
        cout << "                        | " << endl;
        cout << "                        | " << endl;
        cout << "                   [Driveway] " << endl;

		}

	else if (commandWord.compare("go") == 0)
		goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
       	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
         if (command.hasSecondWord()) {
        cout << "you're trying to take " + command.getSecondWord() << endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 )
            cout << "item is not in room" << endl;
        else
            cout << "item is in room" << endl;
            cout << "index number " << + location << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl;
        }
    }

    else if (commandWord.compare("put") == 0)
    {

    }
    /*
    {
    if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
*/
    else if (commandWord.compare("quit") == 0) {
		if (command.hasSecondWord())
			cout << "overdefined input"<< endl;
		else
			return true; /**signal to quit*/
	}
	return false;
}
/** COMMANDS **/
void ZorkUL::printHelp() {
	cout << "valid inputs are; " << endl;
	parser.showCommands();

}

void ZorkUL::goRoom(Command command) {
	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
		return;
	}

	string direction = command.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = currentRoom->nextRoom(direction);

	if (nextRoom == NULL)
		cout << "underdefined input"<< endl;
	else {
		currentRoom = nextRoom;
		cout << currentRoom->longDescription() << endl;
	}
}

string ZorkUL::go(string direction) {
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
		return("direction null");
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
	}
}
