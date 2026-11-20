#include "Menu.h"

void Menu::menu()
{
	while (true)
	{
		std::cout << "\nCurrent folder: " << manager.getCur() << "\n";
		std::cout << "\n1. Go up \\..\n";
		std::cout << "2. Create file (.txt) or folder\n";
		std::cout << "3. View content of current folder\n";
		std::cout << "4. Manage file (.txt)\n";
		std::cout << "5. Delete folder\n";
		std::cout << "6. Change current folder\n";
		std::cout << "0. Exit\n";

		std::cout << "> ";
		std::cin >> choice;
		if (choice == 1) // поднятся на уровень выше в директории
		{
			manager.goUp();
		}
		else if (choice == 2) // создать файл или папку
		{
			while (true)
			{
				std::cout << "\n1. File\n";
				std::cout << "2. Folder\n";
				std::cout << "0. Return\n";
				int choice_2;

				std::cout << "> ";
				std::cin >> choice_2;

				if (choice_2 == 1) // создать файл
				{
					std::string name;
					std::cout << "\nEnter file name:\n> ";
					std::cin >> name;

					if (manager.createFile(name))
						std::cout << "\nFile created\n";
					else
						std::cout << "\nError: file already exists or cannot be created!\n";
				}
				else if (choice_2 == 2) // создать папку
				{
					std::cout << "\nEnter folder name.\n> ";
					std::string name;
					std::cin >> name;

					if (manager.createFolder(name)) {
						std::cout << "\nFolder created\n";
					}
					else {
						std::cout << "\nError: folder already exists or cannot be created!\n";
					}
				}
				else if (choice_2 == 0) // возврат
				{
					break;
				}
			}
		}
		else if (choice == 3) // показать содержимое текущей папки
		{
			auto entries = manager.listDirectory();

			std::cout << "\nCurrent directory: " << manager.getCur() << "\n\n";
			for (const auto& a : entries)
			{
				if (a.is_directory())
				{
					std::cout << "[DIR] ";
				}
				else
				{
					std::cout << "[FILE] ";
				}

				std::cout << a.path().filename() << "\n";
			}

		}
		else if (choice == 4) // управление файлом
		{
			while (true)
			{
				std::cout << "\n1. Read";
				std::cout << "\n2. Edit";
				std::cout << "\n3. Delete";
				std::cout << "\n4. Copy";
				std::cout << "\n5. Cut";
				std::cout << "\n0. Return\n";

				std::cout << "> ";
				int choice_3;
				std::cin >> choice_3;

				if (choice_3 == 1) // прочитать файл
				{
					std::cout << "\nFile name:\n> ";
					std::string fileName;
					std::cin >> fileName;

					std::string content;

					if (manager.readFile(fileName, content))
					{
						std::cout << "\n--- " << fileName << ".txt ---\n\n";
						std::cout << content << "\n";
					}
					else
					{
						std::cout << "\nError reading file!\n";
					}
				}
				else if (choice_3 == 2) // изменить файл
				{
					std::cout << "\n1. Rewrite";
					std::cout << "\n2. Add to end";
					std::cout << "\n0. Return\n> ";

					int choice_4;
					std::cin >> choice_4;

					if (choice_4 == 0)
						return;

					std::string name;
					std::cout << "\nFile name:\n> ";
					std::cin >> name;

					// очистка ввода перед getline
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					std::cout << "\nEnter text (type \"\\x\" on new line to finish):\n";

					std::string text;
					std::string line;

					while (true)
					{
						std::getline(std::cin, line);
						if (line == "\\x")
							break;

						text += line + "\n";
					}

					bool result = false;

					if (choice_4 == 1) // полностью переписать файл
						result = manager.rewrite(name, text);
					else if (choice_4 == 2) // добавить в конец
						result = manager.appendToFile(name, text);

					if (result)
						std::cout << "\nFile updated successfully\n";
					else
						std::cout << "\nError updating file\n";
				}
				else if (choice_3 == 3)
				{
					std::cout << "\nFile name:\n> ";
					std::string fileName;
					std::cin >> fileName;

					std::cout << "\nAre you sure? 1 - Yes, 2 - No\n> ";
					int confirm;
					std::cin >> confirm;

					manager.deleteFile(fileName);
				}
				else if (choice_3 == 4)
				{
					std::cout << "\nFile name:\n> ";
					std::string fileName;
					std::cin >> fileName;

					std::cout << "\nWrite new file name:\n> ";
					std::string toFile;
					std::cin >> toFile;

					if (manager.copyFile(fileName, toFile))
					{
						std::cout << "\nFile successfully copied!\n";
					}
					else
					{
						std::cout << "\nError: File NOT copied!\n";
					}
				}
				else if (choice_3 == 5)
				{
					std::cout << "\nFile name:\n> ";
					std::string fileName;
					std::cin >> fileName;

					std::cout << "\nEnter directory path (for example D:\\MyFolder):\n> ";
					std::string toFile;
					std::cin >> toFile;

					if (manager.cutFile(fileName, toFile))
					{
						std::cout << "\nFile successfully moved!\n";
					}
					else
					{
						std::cout << "\nError: File NOT moved!\n";
					}
				}
				else if (choice_3 == 0)
				{
					break;
				}
			}
		}
		else if (choice == 5) // удаление папки
		{
			std::cout << "\nEnter folder name to delete:\n>";
			std::string name;
			std::cin >> name;

			std::cout << "\nAre you sure? 1 - Yes, 2 - No\n> ";
			int confirm;
			std::cin >> confirm;

			if (confirm == 1)
			{
				if (manager.deleteFolder(name))
					std::cout << "\nFolder deleted\n";
				else
					std::cout << "\nError deleting folder\n";
			}
		}
		else if (choice == 6) // изменить текущую директорию
		{
			std::cout << "\nEnter new directory path (for example D:\\MyFolder):\n> ";
			std::string path;
			std::cin >> path;

			if (manager.changeDirectory(path)) {
				std::cout << "\nCurrent directory changed to: " << manager.getCur() << "\n";
			}
			else {
				std::cout << "\nDirectory does not exist!\n";
			}
		}
		else if (choice == 7)
		{
			return;
		}
	}
}