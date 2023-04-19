#pragma once
#pragma warning(disable : 4996)
#include <string>
#include <iostream>

class Movie
{
public:
	Movie();
	Movie(const uint32_t id, const std::string& title, const uint16_t releaseYear);
	Movie(const Movie& movie);
	Movie(Movie&& movie) noexcept;

	void SetId(const uint32_t id);
	void SetTitle(const std::string& title);
	void SetReleaseYear(const uint16_t releaseYear);

	uint32_t GetId() const;
	std::string GetTitle() const;
	uint16_t GetReleaseYear() const;

	static void ParseMovieData();
	
	Movie& operator=(const Movie& movie);
	Movie& operator=(Movie&& movie) noexcept;
	friend std::ostream& operator<<(std::ostream& out, const Movie& movie);

private:
	uint32_t m_id; 
	std::string m_title;
	uint16_t m_releaseYear;
};
