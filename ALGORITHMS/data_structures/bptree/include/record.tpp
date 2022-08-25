namespace bptree
{
  // <<interface>>
  // Record holds pointer of real data
  template <class Key>
  struct Record
  {
    virtual auto key() -> Key = 0;
    virtual ~Record(){};
  };
}