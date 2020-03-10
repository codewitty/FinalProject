#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
// StdioAndFileStreamer - logging output dual stream helper.
// To see the original source got to the link below.
// Reference : https://stackoverflow.com/questions/24413744/using-operator-to-write-to-both-a-file-and-cout
//
struct StdioAndFileStreamer
{
	StdioAndFileStreamer(std::ostream& out1, std::ostream& out2) : out1_(out1), out2_(out2) {}
	std::ostream& out1_;
	std::ostream& out2_;
};

template <typename T>
StdioAndFileStreamer& operator<<(StdioAndFileStreamer& h, T const& t)
{
	h.out1_ << t;
	h.out2_ << t;
	return h;
}

StdioAndFileStreamer& operator<<(StdioAndFileStreamer& h, std::ostream&(*f)(std::ostream&))
{
	h.out1_ << f;
	h.out2_ << f;
	return h;
}