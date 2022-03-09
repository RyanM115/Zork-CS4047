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
    Room *a, *b, *c, *d, *e, *e1, *f, *g, *h, *i, *j, *k, *l, *m;

    a = new Room("Hallway");
        a->addItem(new Item("x", 1, 11));
        a->addItem(new Item("y", 2, 22));
    b = new Room("Bathroom");
        b->addItem(new Item("xx", 3, 33));
        b->addItem(new Item("yy", 4, 44));
    c = new Room("Sitting Room");
    d = new Room("Front Door");
    e = new Room("Office");
    e1 = new Room("e1");
    f = new Room("Kitchen");
    g = new Room("Utility");
    h = new Room("Garden");
    i = new Room("Driveway");

    j = new Room("Upstairs Hallway");
    k = new Room("Bedroom");
    l = new Room("Bathroom");
    m = new Room("Master Bedroom");

//             (N, E, S, W)
    a->setExits(f, b, d, c);
    b->setExits(g, NULL, NULL, a);
    c->setExits(h, a, NULL, NULL);
    d->setExits(a, e, i, NULL);
    e->setExits(NULL, e1, NULL, d);
    e1->setExits(NULL, NULL, NULL, e);
    f->setExits(NULL, g, a, h);
    g->setExits(NULL, NULL, b, f);
    h->setExits(NULL, f, c, NULL);
    i->setExits(d, NULL, NULL, NULL);

    j->setExits(k, l, m, NULL);
    k->setExits(NULL, NULL, j, NULL);
    l->setExits(NULL, NULL, NULL, j);
    m->setExits(NULL, NULL, NULL, j);

        currentRoom = d;
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
	cout << "start"<< endl;
	cout << "info for help"<< endl;
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
        cout << "      [Garden] ---- [Kitchen] --- [Utility]                            [Bedroom] " << endl;
        cout << "         |              |             |                                    | " << endl;
        cout << "         |              |             |                                    | " << endl;
        cout << "[Sitting Room] ---- [Hallway] --- [Bathroom]                      [Upstairs Hallway] --- [Bathroom] " << endl;
        cout << "                        |                                                  | " << endl;
        cout << "                        |                                                  | " << endl;
        cout << "                  [Front Door] ----- [Office] --- [e1]                      ---- [Master Bedroom] " << endl;
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
