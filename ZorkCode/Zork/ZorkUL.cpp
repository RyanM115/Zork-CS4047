#include <iostream>

using namespace std;
#include "ZorkUL.h"

int main(int argc, char *argv[]) {
    ZorkUL temp;
    temp.play();
    return 0;
}

ZorkUL::ZorkUL() {
    createRooms();
}

void ZorkUL::createRooms()  {
    Room *a, *b, *c, *d, *e, *e1, *f, *g, *h, *i, *j, *k, *l, *m, *o;

   //Downstairs
    a = new Room("Downstairs Hallway."
                 " This is quite a large hallway with a wide, wooden, "
                 " helix stairs ahead."
                 " To the east, a bathroom with the door ajar."
                 " West, a crowded sitting room.");
    b = new Room("Bathroom."
                 " You are greeted by the groaning of a drunk man "
                 " folded into the corner of the bathroom."
                 " Nothing else here other than some pills on the locker.");
        b->addItem(new Item("Unknown Pills", 3, 33));
    c = new Room("Sitting Room."
                 " This room is quite busy. There must be 50 people in here. "
                 " There is a large gathering around one man. "
                 " He seems to be lecturing the other guests. "
                 " Intel suggests he is a university lecturer. Dr.Chris Exton."
                 " Nothing else important here.");
        c->addItem(new Item("TV Remote", 1, 22));
        c->addItem(new Item("Glass of Wine", 3, 33));
        c->addItem(new Item("Empty Glass", 3, 33));
    d = new Room("Front Door."
                 " You're in the house. Ahead, a large hallway. "
                 " To the east a room we believe to be an office."
                 " The place is crowded. People are looking at you weird so get a move on.");
    e = new Room("Office."
                 " This must be the targets office."
                 " He posseses many books."
                 " A fan of history, particularly war based history."
                 " Behind his desk, a wide, plain wall,"
                 " approximately two foot further out than the rest of the wall."
                 " Around the corner of said protruding wall, a keypad."
                 " We need that code");
        e->addItem(new Item("Pen", 1, 10));
    e1 = new Room("Unknown");
    f = new Room("Kitchen."
                 " All work in here."
                 " Chefs and waiters walking with purpose.");
        f->addItem(new Item("Knife", 4, 33));
    g = new Room("Utility."
                 " This must be the quietest room in the house."
                 " Not a soul in here");
        g->addItem(new Item("Screwdriver", 3, 33));
    h = new Room("Garden."
                 " This is where most of the guests are."
                 " Everyone eating , drinking, sharing anecdotes"
                 " The waiters push out as much food and drink as they can."
                 " South lies a shed");
        h->addItem(new Item("Glass of Wine", 3, 33));
        h->addItem(new Item("Empty Glass", 3, 33));
        h->addItem(new Item("Empty Glass", 3, 33));
    i = new Room("Driveway."
                 " You're outside. Guests are both heading into the party and leaving it."
                 " Cars are flooding the driveway. Head inside");
    //Upstairs
   j = new Room("Upstairs Hallway."
                 " It's quiet up here. Down the hall there are bedrooms and a bathroom."
                 " Have a look around.");
    k = new Room("Bedroom."
                 " Seems to be a sort of guest bedroom."
                 " Looks like nobody has used it in a while.");
    l = new Room("Bathroom."
                 " There's nobody in here"
                 " The mirror over the sink is cracked."
                 " Theres water all over the floor"
                 " Seems to be a drop of blood running through the water");
    m = new Room("Master Bedroom.");
    o = new Room("Shed."
                 " Typical shed, webs on every corner, creaky floors."
                 " There's tools on the wall");
        o->addItem(new Item("Shovel", 10, 33));
        o->addItem(new Item("Axe", 10, 33));

//             (N, E, S, W)
    a->setExits(j, b, d, c);
    b->setExits(g, NULL, NULL, a);
    c->setExits(h, a, NULL, NULL);
    d->setExits(a, e, i, NULL);
    e->setExits(NULL, e1, NULL, d);
    e1->setExits(NULL, NULL, NULL, e);
    f->setExits(NULL, g, NULL, h);
    g->setExits(NULL, NULL, b, f);
    h->setExits(o, f, c, NULL);
    i->setExits(d, NULL, NULL, NULL);

    j->setExits(a, l, m, k);
    k->setExits(NULL, j, NULL, NULL);
    l->setExits(NULL, NULL, NULL, j);
    m->setExits(j, NULL, NULL, j);
    o->setExits(NULL, NULL, h, NULL);

    rooms.push_back(*a);
    rooms.push_back(*b);
    rooms.push_back(*c);
    rooms.push_back(*d);
    rooms.push_back(*e);
    rooms.push_back(*f);
    rooms.push_back(*g);
    rooms.push_back(*h);
    rooms.push_back(*i);
    rooms.push_back(*j);
    rooms.push_back(*k);
    rooms.push_back(*l);
    rooms.push_back(*m);
    rooms.push_back(*o);

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
        cout << "                                                  Morrissey Manor " << endl;
        cout << "                        Downstairs                                                    Upstairs" << endl;
        cout << " " << endl;
        cout << "      [Shed] " << endl;
        cout << "         | " << endl;
        cout << "         | " << endl;
        cout << "      [Garden] ---- [Kitchen] -------------[Utility]                        [Upstairs Hallway] " << endl;
        cout << "         |                                     |                                    | " << endl;
        cout << "         |                                     |                                    | " << endl;
        cout << "[Sitting Room] -- [Downstairs Hallway] --- [Bathroom]                  [Bedroom]---   ---- [Bathroom] " << endl;
        cout << "                            |                                                       | " << endl;
        cout << "                            |                                                       | " << endl;
        cout << "                      [Front Door] ----- [Office] --- [Unknown]                       ---- [Master Bedroom] " << endl;
        cout << "                            | " << endl;
        cout << "                            | " << endl;
        cout << "                       [Driveway] " << endl;

        }

    else if (commandWord.compare("go") == 0)
        goRoom(command);
    else if (commandWord.compare("teleport") == 0)
            teleport();
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

string ZorkUL::teleport() {
    currentRoom = &rooms.at((int) rand() % rooms.size());
        cout << currentRoom->longDescription() << endl;
        return "Teleportation Successfull";
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
