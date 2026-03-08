#include "Shapes/Star2D.h"
#include "Shapes/Line2D.h"
#include "Math/Utils.h"
#include "Shapes/Rectangle2D.h"
//#include "App.h"
#include <random>
#include <algorithm>

Star2D::Star2D(const Vector2D& center, uint8_t spikeNum, float centerSpikeDist, float spikeLength) :
	numberOfSpikes_(spikeNum), centerSpikeDist_(centerSpikeDist), 
	spikeLength_(spikeLength), center_(center)
{
	ValidateSpikeNumber();
	n_ = (numberOfSpikes_ - 1) / 2;
	CreateStar();
}
/*
Star2D Star2D::GenerateStar()
{
	// Create a star with random parameters
	int spikes = math::GetRandom(3, 9);
	float centerDist = math::GetRandom(10, 50);
	float spikeLength = math::GetRandom(10, 50);
	Vector2D center(math::GetRandom(0, App::Instance().GetWidth()),
		math::GetRandom(0, App::Instance().GetHeight()));

	return Star2D(center, spikes, centerDist, spikeLength);
}

std::vector<Star2D> Star2D::GetSortedStars(unsigned int starNum)
{
		std::vector<Star2D> stars;
		for (unsigned int i = 0; i < starNum; ++i)
		{
			stars.push_back(Star2D::GenerateStar());
		}
		//sort the stars by radius
		std::sort(stars.begin(), stars.end(), [](const Star2D& a, const Star2D& b) {
			return a.GetRadius() < b.GetRadius();
			});
		return stars;
}*/

void Star2D::CreateStar()
{
	//first line of the star is; left line part of the top first pike
	Vector2D firstLineEnd = Vector2D(center_.GetX(), center_.GetY() - centerSpikeDist_);
	Vector2D firstLineStart = Vector2D(center_.GetX(), firstLineEnd.GetY() - spikeLength_);
    
	Line2D firstLine{ firstLineStart, firstLineEnd };
	bool flipFlop = true;

	//radian
	float innerAngle = math::PI * (1.0f - ((2.0f * n_) / numberOfSpikes_));
	float outerAngle = math::PI * (1 - (2.0f * (n_ - 1)) / numberOfSpikes_);

	firstLine.Rotate(innerAngle / 2.0f, firstLine.GetPointStart());
	lines_.push_back(firstLine);
	Line2D nextLine = firstLine;

	for (int i = 1; i < (numberOfSpikes_ * 2); ++i)
	{
		
			//rotate the line by the amount of spike inner angle
			if (flipFlop)
			{
				nextLine.Rotate(-outerAngle, nextLine.GetPointEnd());
			}
			//rotate the line by the amount of spike outer degree
			else
			{
				nextLine.Rotate(innerAngle, nextLine.GetPointStart());
			}
			flipFlop = !flipFlop;
			lines_.push_back(nextLine);
	}

	for(const Line2D& line : lines_)
	{
		points_.push_back(line.GetPointStart());
		points_.push_back(line.GetPointEnd());
	}
}

void Star2D::ValidateSpikeNumber()
{
	if (numberOfSpikes_ % 2 == 0)
	{
		--numberOfSpikes_;
	}

	if (numberOfSpikes_ < 3)
	{
		numberOfSpikes_ = 3;
	}
}


bool Star2D::ContainsPoint(const Vector2D& point) const
{
	uint8_t crossing{ 0 };
	for (const auto& line : lines_)
	{
		Vector2D sp = line.GetPointStart();
		Vector2D ep = line.GetPointEnd();
		//if statement checks if the point in between the line so it can cross
		if((sp.GetY() > point.GetY()) != (ep.GetY() > point.GetY())) 
		{
			// if 0.5 then moved half of the way etc.
			float fractionMoveY = (point.GetY() - sp.GetY()) / (ep.GetY() - sp.GetY());
			//find movement in x
			float FractionMoveX = fractionMoveY * (ep.GetX() - sp.GetX());
			//find the x coordinate of the crossing point
			float crossX = sp.GetX() + FractionMoveX;

			if (point.GetX() < crossX)
			{
				++crossing;
			}
		}

	}
	// if crossing is odd then it is inside of the star else it is outside of the star
		return crossing % 2 == 1;
	
	
}

Rectangle2D Star2D::GetBoundingBox() const
{
	float minX = center_.GetX();
	float maxX = center_.GetX();
	float minY = center_.GetY();
	float maxY = center_.GetY();

	for (const auto& line : lines_) {
		const Vector2D& sp = line.GetPointStart();
		const Vector2D& ep = line.GetPointEnd();

		minX = std::min({minX, sp.GetX(), ep.GetX()});
		maxX = std::max({maxX, sp.GetX(), ep.GetX()});
		minY = std::min({minY, sp.GetY(), ep.GetY()});
		maxY = std::max({maxY, sp.GetY(), ep.GetY()});
	}

	Vector2D topLeft(minX, minY);
	Vector2D bottomRight(maxX, maxY);
	return Rectangle2D(topLeft, bottomRight);
}

void Star2D::MoveTo(const Vector2D& newPos)
{
	Vector2D moveOffset = newPos - GetCenter();
	MoveBy(moveOffset);
	center_ = newPos;
}
