#include "../include/MovieInformationDisplayer.h"
#include <iomanip>
#include <vector>
#include <algorithm>

MovieInformationDisplayer::MovieInformationDisplayer(uint32_t id, const std::string& title, const uint16_t releaseYear, const std::string genres)
	: m_movieId(id)
	, m_title(title)
	, m_releaseYear(releaseYear)
	, m_genres(genres)
{
}

void MovieInformationDisplayer::AddGenre(const std::string& genre)
{
	if (m_genres.size() == 0)
		m_genres = genre;
	else {
		m_genres.append(", ");
		m_genres.append(genre);
	}
}

uint32_t MovieInformationDisplayer::GetMovieId() const
{
	return m_movieId;
}

std::string MovieInformationDisplayer::GetTitle() const
{
	return m_title;
}

uint16_t MovieInformationDisplayer::GetReleaseYear() const
{
	return m_releaseYear;
}

std::string MovieInformationDisplayer::GetGenres() const
{
	return m_genres;
}


std::ostream& operator<<(std::ostream& g, const MovieInformationDisplayer& mid)
{
	std::vector<std::string> propertyRows;
	propertyRows.emplace_back(" Movie id: " + std::to_string(mid.m_movieId));
	propertyRows.emplace_back(" Title: " + mid.m_title);
	propertyRows.emplace_back(" Genres: " + mid.m_genres);

	size_t maxLength = std::max_element(propertyRows.begin(), propertyRows.end(),
		[](const std::string& a, const std::string& b) {
			return a.size() < b.size();
		})->size() + 1;
	g << '\n';
	for (int i = 0; i <= maxLength + 1; ++i)
		g << NamedAsciiChars::DOTTED_BLOCK;
	g << '\n';
	for (const auto& row : propertyRows)
		g << NamedAsciiChars::DOTTED_BLOCK << row << std::setfill(' ') << std::setw(maxLength - row.size() + 1) << NamedAsciiChars::DOTTED_BLOCK << '\n';
	for (int i = 0; i <= maxLength + 1; ++i)
		g << NamedAsciiChars::DOTTED_BLOCK;
	g << "\n\n";
	return g;
}