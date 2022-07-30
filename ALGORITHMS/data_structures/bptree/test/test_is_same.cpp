#include <gtest/gtest.h>
#include <memory>
#include <iostream>

class IsSameFixture : public ::testing::Test
{
protected:
  struct AbstNode
  {
    virtual auto someOperation() -> int = 0;
    virtual ~AbstNode() { std::cout << "~AbstNode()\n"; };
  };

  struct ANode : public AbstNode
  {
    auto someOperation() -> int override { return 0; }
    ~ANode() override { std::cout << "~ANode()\n"; }

  private:
    int padding[16];
  };

  struct BNode : public AbstNode
  {
    auto someOperation() -> int override { return 1; }
    ~BNode() override { std::cout << "~BNode()\n"; }

  private:
    int padding[64];
  };
};

TEST_F(IsSameFixture, DeclType)
{
  AbstNode *aP = new ANode{};
  EXPECT_TRUE((std::is_same<decltype(*aP), IsSameFixture::AbstNode &>::value));
  std::unique_ptr<AbstNode> bP = std::make_unique<BNode>();
  EXPECT_TRUE((std::is_same<decltype(*bP), IsSameFixture::AbstNode &>::value));
  EXPECT_TRUE(dynamic_cast<ANode *>(aP));
  EXPECT_FALSE(dynamic_cast<BNode *>(aP));
  EXPECT_TRUE(dynamic_cast<BNode *>(bP.get()));
  EXPECT_FALSE(dynamic_cast<ANode *>(bP.get()));
}

TEST_F(IsSameFixture, HasSameSize)
{
  AbstNode *pA = new ANode{};
  AbstNode *pB = new BNode{};
  EXPECT_EQ(sizeof(*pA), sizeof(*pB));
  std::cout << "sizeof(ANode) = " << sizeof(ANode) << ", sizeof(*pA) = " << sizeof(*pA) << "\n";
  std::cout << "sizeof(BNode) = " << sizeof(BNode) << ", sizeof(*pB) = " << sizeof(*pB) << "\n";
}

TEST_F(IsSameFixture, DeathTest)
{
  // 만약에 pA자리에 BNode로 placement new를 수행한다면?

  // AbstNode *pA = new ANode{};
  // AbstNode *pAToB = new (pA) BNode{};

  // EXPECT_DEATH({ pAToB->~AbstNode(); pA->~AbstNode(); }, "abort");

  // free 시에 잘못된 메모리를 해제하여 예외가 발생한다.
}