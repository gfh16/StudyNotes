#ifndef _QUAD_H_
#define _QUAD_H_

//______________________________________________________________________________
class Quad
{
      public:
        Quad();
        Quad(Float_t a, Float_t b, Float_t c);
        ~Quad();
        Float_t Evaluate(Float_t x) const;
        void Solve() const;

      private:
        Float_t fA;
        Float_t fB;
        Float_t fC;
};

#endif
