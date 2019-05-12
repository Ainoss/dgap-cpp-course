
#include <iostream>
#include <math.h>

using namespace std;

class C {

	public :

		double re;
		double im;

        friend C operator + (double x, C c1);
   		friend C operator - (double x, C c1);
		friend C operator * (double x, C c1);
		friend C operator / (double x, C c1);
		friend bool operator == (double x, C c1);
		friend bool operator != (double x, C c1);

        C () {}

		C (double re1, double im1) {
			this -> re = re1;
			this -> im = im1;
		}

		C (double re1) {
			this -> re = re1;
			this -> im = 0;
		}

		C (const C& c1) {
			this -> re = c1.re;
			this -> im = c1.im;
		}

		double abs() {
            return (sqrt(this -> re * this ->re + this -> im* this ->im));
        }

		C operator + (C c1) {
			return C(this -> re + c1.re, this -> im + c1.im);
		}

		C operator - (C c1) {
			return C (this -> re - c1.re, this -> im - c1.im);
		}

		C operator * (C c1) {
			return C (this -> re * c1.re - this -> im * c1.im, this -> re * c1.im + this -> im * c1.re);
		}

		C operator / (C c1) {
			return C \
            ((this -> re * c1.re +\
            this -> im * c1.im)/(this -> re * this -> re + this -> im * this -> im), \
            (this -> re * c1.im - this \
            -> im * c1.re)/(this -> re * this -> re\
            + this -> im * this -> im) );
		}

		bool operator == (C c1) {
			if ((this -> re == c1.re) && (this -> im == c1.im)) {
				return 1;
			}
			else {
				return 0;
			}
		}

		bool operator != (C c1) {
			if ((this -> re == c1.re) && (this -> im == c1.im)) {
				return 0;
			}
			else {
				return 1;
			}
		}

		C operator + (double x) {
			return C (this -> re + x, this -> im );
		}

		C operator - (double x) {
			return C (this -> re - x, this -> im );
		}

		C operator * (double x) {
			return C (this -> re * x, this -> im * x);
		}

		C operator / (double x) {
			return C ((this -> re / x, this -> im / x));
		}

		bool operator == (double x) {
			if ((this -> re == x) && (sqrt(this -> im * this -> im) < 0.00000001)) {
				return 1;
			}
			else {
				return 0;
			}
		}

		bool operator != (double x) {
			if ((this -> re == x) && (sqrt (this -> im* this -> im) < 0.00000001)) {
				return 0;
			}
			else {
				return 1;
			}
		}

    	friend ostream& operator << (ostream & os, C c1) {
			return os << c1.re << " " << c1.im ;
		}
};

C operator + (double x, C c1) {
	return C (c1.re + x, c1.im );
}

C operator - (double x, C c1) {
	return C (c1.re - x, c1.im );
}

C operator * (double x, C c1) {
	return C (c1.re * x, c1.im * x);
}

C operator / (double x, C c1) {
	return C ((c1.re / x, c1.im / x));
}

bool operator == (double x, C c1) {
	if ((c1.re == x) && (sqrt (c1.im * c1.im) < 0.00000001)) {
		return 1;
	}
	else {
		return 0;
	}
}

bool operator != (double x, C c1) {
	if ((c1.re == x) && (sqrt(c1.im*c1.im) < 0.00000001)) {
		return 0;
	}
	else {
		return 1;
	}
}
