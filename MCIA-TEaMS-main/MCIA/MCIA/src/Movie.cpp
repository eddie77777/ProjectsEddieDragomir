#include "../include/Movie.h"
#include "../include/DatabaseManagement.h"

Movie::Movie()
	:m_id(0)
	, m_title()
	, m_releaseYear(0)
{}

Movie::Movie(const uint32_t id, const std::string& title, const uint16_t releaseYear)
	: m_id(id)
	, m_title(title)
	, m_releaseYear(releaseYear)
{}

Movie::Movie(const Movie& movie)
{
	*this = movie;
}

Movie::Movie(Movie&& movie) noexcept
{
	*this = std::move(movie);
}

void Movie::SetId(const uint32_t id)
{
	m_id = id;
}
void Movie::SetTitle(const std::string& title)
{
	m_title = title;
}

void Movie::SetReleaseYear(const uint16_t releaseYear)
{
	m_releaseYear = releaseYear;
}

uint32_t Movie::GetId() const
{
	return m_id;
}

std::string Movie::GetTitle() const
{
	return m_title;
}

uint16_t Movie::GetReleaseYear() const
{
	return m_releaseYear;
}

Movie& Movie::operator=(const Movie& movie)
{
	m_id = movie.m_id;
	m_title = movie.m_title;
	m_releaseYear = movie.m_releaseYear;
	return *this;
}

Movie& Movie::operator=(Movie&& movie) noexcept
{
	m_id = movie.m_id;
	m_title = movie.m_title;
	m_releaseYear = movie.m_releaseYear;
	new(&movie) Movie;
	return *this;
}

void Movie::ParseMovieData()
{
	auto& storage = DatabaseManagement::GetInstance().GetStorage();
	auto allMovies = storage.select(columns(&MovieIntermediary::GetId, &MovieIntermediary::GetTitle, &MovieIntermediary::GetGenre));

	std::cout << allMovies.size() << '\n';
	uint32_t id = 0;
	uint32_t old_id = 0;
	for (auto& tpl : allMovies)
	{
		std::string title = get<1>(tpl);
		std::string sreleaseYear = "";
		for (size_t index = title.size() - 5; index <= title.size() - 2; index++)
			sreleaseYear.push_back(title[index]);
		try {
			int releaseYear = std::stoi(sreleaseYear);
			std::string new_title = "";
			for (int i = 0; i < title.size() - 6; i++)
				new_title.push_back(title[i]);
			Movie m(id++, new_title, releaseYear);
			DatabaseManagement::GetInstance().GetStorage().replace(m);
		}
		catch (std::invalid_argument e)
		{
			Movie m(id++, std::get<1>(tpl), -1);
			DatabaseManagement::GetInstance().GetStorage().replace(m);
		}
		old_id = get<0>(tpl);
		std::cout << old_id << id << '\n';
		//movie_counter++;
		//std::cout << movie_counter << '\n';
	}
}

std::ostream& operator<<(std::ostream& out, const Movie& movie)
{
	return out << movie.GetId() << " " << movie.GetTitle();
}
