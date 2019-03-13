float tri  ( Vec, Vec, Vec );

class Tet {
public:
	Vec A, B, C, D;
	// constructors
	Tet(): A(Vec(0,0,0)), B(Vec(1,0,0)), C(Vec(0,1,0)), D(Vec(0,0,1)) {}
	Tet( Vec a, Vec b, Vec c, Vec d): A(a), B(b), C(c), D(d) {}
	Tet( Seg a, Seg b ): A(a.A), B(a.B), C(b.A), D(b.B) {}
	// operators
	Seg operator + ( const Seg &s ) const {	// return s added to the end of the current segment (NB: a+b != b+a) 
		return Seg( A, B+s.B-s.A );
	}
	Seg operator + ( const Vec &v ) const {	// return v added to the end of the current segment
		return Seg( A, B+v );
	}
	Seg operator - ( const Seg &s ) const {	// return s subtracted from the end of the current segment (NB: a-b != b-a) 
		return Seg( A, B-s.B+s.A );
	}
	Seg operator - ( const Vec &v ) const {	// return v subtracted from the end of the current segment
		return Seg( A, B-v );
	}
	void operator += ( const Seg &s ) {	// add s to the end of the current segment (NB: a+=b != b+=a) 
		B += s.B-s.A;
	}
	void operator -= ( const Seg &s ) {	// subtract s from current segment (NB: a-=b != b-=a) 
		B -= s.B+s.A;
	}
	void operator += ( const Vec &v ) {	// append vector v to end of current segment
		B += v;
	}
	void operator -= ( const Vec &v ) {	// subtract vector v from end of current segment
		B -= v;
	}
	float operator * ( const Seg &s ) const {	// dot product of the line vectors (same as pdotp())
		return (B-A)*(s.B-s.A);
	}
	float operator ^ ( const Seg &s ) const {	// triple product of the line vectors with A-A vector (= pvol())
		return tri(B-A, s.B-s.A, s.A-B);
	}	 
	float operator  | ( const Seg &s ) const;	// contact normal distance (-ve = none)
	float operator || ( const Seg &s ) const;	// dito squared
	// inline functions
	inline float len () const { return (B-A).len(); }
	inline Vec vec () const { return B-A; }		// line vector
	inline Vec vec ( const float s ) const { return (B-A).getNorm()*s; }	// line vector of length s (at A)
	inline Vec mid () const { return B&A; }		// mid point (& = Vec.ave)
	// functions
	bool	vec_in_seg  ( const Vec& ) const; 	// TRUE if c lies over the line segment
	float	vec_to_line ( const Vec& ) const;	// returns the distance of c to extended A-B line segment
	Vec	vec_on_line ( const Vec& ) const;	// returns the image of Vec on extended line segment
	Vec  hit_trif  ( const Vec&, const Vec&, const Vec& ) const;	// line-plane intersection point (fractional)
	Vec  hit_tri   ( const Vec&, const Vec&, const Vec& ) const;	// intersection point (real)
	Vec  hit_tri   ( const Vec&, const Vec&, const Vec&, const Vec& ) const;	// intersection point (given trif)
	bool cut_tri   ( const Vec& ) const;	// TRUE if segment intersects the triangle (given fractional point trif)
	bool cut_tri   ( const Vec&, const Vec&, const Vec& ) const;	// TRUE if segment intersects the triangle
	bool cut_plane ( const Vec& ) const;	// TRUE if segment intersects the triangle (given fractional point)
	bool cut_plane ( const Vec&, const Vec&, const Vec& ) const;	// TRUE if segment intersects the triangle
	void separate ( float, float );	// separate the endpoints towards a dist by fraction a kick
	void separate ( float );	// separate the endpoints to a dist
};
