class Bird {
private:
  int _x;
  int _y;
  int _r;
  int _v;
  int _a;

public:
  Bird(int x, int y, int r) {
    _x = x;
    _y = y;
    _r = r;
    _v = 0;
    _a = 0;
  }

  int getX() {
    return _x;
  }

  int getY() {
    return _y;
  }

  int getR() {
    return _r;
  }

  int getV() {
    return _v;
  }

  void update(int force) {
    _a = 0;
    _a += force;
    _v += _a;
    _y += _v;
  }
};
