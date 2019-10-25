#ifndef BOX_H
#define BOX_H

class Box
{
	public:
          Box();
	  Box(double LenValue, double WidValue, double HeiValue);
          double volume() const;
	  int compareVolume(const Box& box2) const;
          int getObjectCount() const;

        private:
          static int objectCount;
	  double length;
	  double width;
	  double height;
          
};

#endif
