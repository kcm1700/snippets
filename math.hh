template<typename Integer, int n = sizeof(Integer)*4> struct _HelperGetNextPower2
{
    static Integer function(Integer value)
    {
        return _HelperGetNextPower2<Integer, n/2>::function(value | (value >> n));
    }
};
template<typename Integer> struct _HelperGetNextPower2<Integer, 0>
{
    static Integer function(Integer value)
    {
        return value;
    }
};
/// returns the power of two which is large or equal to given value
template<typename Integer> inline Integer GetNextPower2(Integer value)
{
    return _HelperGetNextPower2<Integer>::function(value-1)+1;
}
