#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <string>
#include <vector>
#include <iostream>

//expresses gameplay through dialogue messages allowing a play to make a decision
class Dialogue
{
	private:

	// Initial piece of information that the dialogue displays
	std::string description;
	// A vector of choices
	std::vector<std::string> choices;

	public:

	// Run the dialogue
	int activate()
	{
		// Output the information
		std::cout << description << std::endl;

		// Output and number the choices
		for(int i = 0; i < this->choices.size(); ++i)
		{
			std::cout << i+1 << ": " << this->choices[i] << std::endl;
		}

		int userInput = -1;


		while(true)
		{
			std::cin >> userInput;

			if(userInput >= 0 && userInput <= choices.size())
			{
				return userInput;
			}
		}

		return 0;
	}

	Dialogue(std::string description, std::vector<std::string> choices)
	{
		this->description = description;
		this->choices = choices;
	}

	Dialogue()
	{
	}
};

#endif /* DIALOGUE_HPP */
