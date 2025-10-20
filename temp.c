double seno(double angle, int precision) {
  double term = angle;
  double result = term;
  for (int i = 1; i < precision; ++i) {
    term *= -1 * (angle * angle) / ((2 * i) * (2 * i + 1));
    result += term;
  }
  return result;
}
