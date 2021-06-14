class Pipe {
private:
  int _x;
  int _y;
  int _w;
  int _h;
  int _v;

public:
  Pipe(int x, int y, int w) {
    _x = x;
    _y = y;
    _w = w;
    _h = random(32,64);
    _v = -1;
  }

  int getX() {
    return _x;
  }

  int getY() {
    return _y-_h;
  }

  int getW() {
    return _w;
  }

  int getH() {
    return _h;
  }

  void update() {
    _x += _v;
  }

  void reset() {
    _x = SCREEN_WIDTH;
    _h = random(32,64);
  }
};
