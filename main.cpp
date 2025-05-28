#include <iostream>
#include <list>

#define CONTINUE_SENTINEL 'C'
#define QUIT_SENTINEL 'Q'

#define STOP_SENTINEL "S"
#define REMOVAL_SENTINEL "R"

using namespace std;

const int BUFFER_LEN = 1'000;

void clearBuffer()
{
    cin.clear();
    cin.ignore(::BUFFER_LEN, -1);
}

void displayWelcomeMessage()
{
    cout << "WELCOME!\nThis proram will list and process fruits.\n\n";
}

void displayFruits(const list<string> &fruits)
{
    cout << "List of Fruits:\n";

    for (const string &fruit : fruits)
        cout << " - " << fruit << "\n";
}

string lowercaseStr(string &str)
{
    string copy = str;

    for (int i = 0; i < str.size(); i++)
    {
        copy[i] = tolower(str[i]);
    }

    return copy;
}

void promptFruit(list<string> &fruits)
{
    string input, longest = "";

    while (input != STOP_SENTINEL)
    {
        // Prompt for a fruit
        cout << "Enter a fruit to list (" << STOP_SENTINEL << " - Stop | "
             << REMOVAL_SENTINEL << " - Remove): ";
        cin >> input;

        if (cin.fail())
        {
            clearBuffer();
            return;
        }

        // Input Check
        // Stop Sentinel - Immediate Termination
        if (input == STOP_SENTINEL)
        {
            // Display and Terminate
            cout << "\nOUTPUT\n";

            // Display Sorted Fruits
            cout << "Sorted Fruits in Ascending Order: ";
            for (const string &fruit : fruits)
                cout << fruit << ", ";
            cout << "\n";

            // Display the longest fruit
            cout << "Longest Fruit: " << longest << "\n";

            // Display the fruit count
            cout << "Number of fruits listed: " << fruits.size() << "\n";

            return;
        }

        // Removal Sentinel
        else if (input == REMOVAL_SENTINEL)
        {
            // Display the list of fruits for fruit removal selection
            displayFruits(fruits);

            // Continuously prompt for a fruit to remove until a valid input is
            // received
            string rFruit = "";

            while (rFruit.empty())
            {
                cout << "Please enter a fruit to remove: ";
                cin >> rFruit;

                if (cin.fail())
                {
                    clearBuffer();
                    cout << "Please enter a valid fruit!\n";
                    rFruit = "";
                }

                for (auto pos = fruits.begin(); pos != fruits.end();)
                {
                    string fruit = *pos;
                    bool remove = true;

                    for (int i = 0; i < fruit.size(); i++)
                    {
                        const char &fch = fruit[i], rch = rFruit[i];

                        if (tolower(fch) == tolower(rch))
                            continue;

                        remove = false;
                    }

                    if (remove)
                        pos = fruits.erase(pos);
                    else
                        pos++;
                }

                displayFruits(fruits);
            }
        }

        // Otherwise, proceed to listing more fruits
        else
        {
            bool invalid = false;
            for (const char &ch : input)
            {
                if (isalpha(ch))
                    continue;

                cout
                    << "Input must only contain letters within the alphabet!\n";

                invalid = true;
                break;
            }

            if (invalid)
                continue;

            fruits.push_back(input);

            // Sort the fruits (Ascending)
            fruits.sort([](string &a, string &b)
                        { return lowercaseStr(a) < lowercaseStr(b); });

            // Find the longest word
            if (input.size() > longest.size())
                longest = input;

            displayFruits(fruits);

            // Proceed
            continue;
        }
    }
}

int main()
{
    displayWelcomeMessage();

    // Program Loop
    while (true)
    {
        // Prompt user for fruits
        list<string> fruits;
        promptFruit(fruits);

        char choice;
        while (choice != CONTINUE_SENTINEL && choice != QUIT_SENTINEL)
        {
            cout << "Enter a procedural option (" << CONTINUE_SENTINEL
                 << " - Continue | " << QUIT_SENTINEL << " - Quit): ";
            cin >> choice;

            if (cin.fail())
            {
                clearBuffer();
                cout << "Please enter a valid sentinel option!\n";
            }
        }

        // If C, proceed to making a new list of fruits
        if (choice == CONTINUE_SENTINEL)
        {
            choice = ' ';
            continue;
        }

        // Otherwise, terminate the program
        else
        {
            cout << "\nTHANK YOU!\n";
            break;
        }
    }

    return 0;
}
