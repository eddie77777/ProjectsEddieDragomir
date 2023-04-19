#include "../include/Genre.h"
#include "../include/DatabaseManagement.h"

Genre::Genre(const std::string& name)
	: m_name(name)
	, m_id(0)
{}

Genre::Genre(const uint16_t id, const std::string& name)
	: m_id(id)
	, m_name(name)
{}

void Genre::SetId(const uint16_t id)
{
	m_id = id;
}

void Genre::SetName(const std::string& name)
{
	m_name = name;
}

uint16_t Genre::GetId() const
{
	return m_id;
}

std::string Genre::GetName() const
{
	return m_name;
}

void Genre::ParseGenres()
{
	auto& storage = DatabaseManagement::GetInstance().GetStorage();
	auto moviesGenres = storage.select(columns(&MovieIntermediary::GetGenre));
	int id = 1;
	Genre g0(0, "Unknown");
	DatabaseManagement::GetInstance().GetStorage().replace(g0);
	int count = 0;
	for (auto& tpl : moviesGenres)
	{
		bool OK = 0;
		std::string name = get<0>(tpl);
		std::string genre = "";
		for (int i = 0; i < name.size(); i++)
		{
			if (name[i] == '|' || i == name.size() - 1)
			{
				Genre g(id, genre);
				auto genres = storage.select(columns(&Genre::GetName));
				for (auto& genreName : genres)
				{
					if (get<0>(genreName) == genre)
					{
						OK = 1;
					}
				}
				if (OK == 0)
				{
					DatabaseManagement::GetInstance().InsertElement(g);
					id++;
				}
				genre = "";
				i++;
			}
			genre.push_back(name[i]);
		}
		count++;
		if (count % 1000 == 0)
			std::cout << "Verified rows: " << count << '\n';
	}
}
