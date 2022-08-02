/// https://stackoverflow.com/a/16340122/6428901
/// 수학에서 사용하는 range 구문을 사용한 비교연산자

namespace ranged_compare
{
  struct LeftOpen
  {
    template <class T>
    static bool Compare(const T &value, const T &range) { return range <= value; }
  };
  struct LeftClosed
  {
    template <class T>
    static bool Compare(const T &value, const T &range) { return range < value; }
  };
  struct RightOpen
  {
    template <class T>
    static bool Compare(const T &value, const T &range) { return value <= range; }
  };
  struct RightClosed
  {
    template <class T>
    static bool Compare(const T &value, const T &range) { return value < range; }
  };
  template <class L, class R, class T>
  bool IsInRange(const T &value, const T &min, const T &max) { return L::template Compare<T>(value, min) && R::template Compare<T>(value, max); }
  template <class CMP, class T>
  bool IsInRange(const T &value, const T &compareTo) { return CMP::template Compare<T>(value, compareTo); }

} // namespace ranged_compare
