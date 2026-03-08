#pragma once
#include <stdint.h>
#include <vector>
#include "Math/Vector2D.h"
#include "Shape.h"


class Line2D;
class Rectangle2D;

class Star2D : public Shape
{
	uint8_t numberOfSpikes_;
	float centerSpikeDist_;
	Vector2D center_;
	float spikeLength_;	
	//n is a number how many steps jump to connect another spike
	uint8_t n_;
	std::vector<Line2D> lines_;
	//is david star kind or hollow star kind
	bool innersIntersect_;
	/* 
	*180 – 360n_/numberOfSpikes_ = 180(1 – 2n_/numberOfSpikes_) formula for inner angle 
	* 180(1 – 2(n_ – 1)/numberOfSpikes_) formula for outer angle
	*/
	void CreateStar();
	void ValidateSpikeNumber();

public:
	Star2D(const Vector2D& center) :Star2D(center, 5) {};
	Star2D(const Vector2D& center,
		uint8_t spikeNum = 5, 
		float centerSpikeDist = 20.0f, 
		float spikeLength = 30.0f);
	inline unsigned int GetRadius() const { return centerSpikeDist_ + spikeLength_; }

	//static Star2D GenerateStar();
	//static std::vector<Star2D> GetSortedStars(unsigned int starNum);


	//even/odd line crossing algorim to determine if a point is inside of the star
	virtual bool ContainsPoint(const Vector2D& point) const override;
	virtual Vector2D GetCenter() const override { return center_; }
	virtual Rectangle2D GetBoundingBox() const override;
	virtual void MoveTo(const Vector2D& newPos) override;
	virtual std::optional<std::vector<Line2D>> GetLines() const override { return lines_; }

};

