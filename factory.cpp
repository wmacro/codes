#include <iostream>
#include <memory>

// 基类 Product
class Product {
public:
    virtual void use() const = 0;
    virtual ~Product() = default;
};

// 派生类 ConcreteProductA
class ConcreteProductA : public Product {
public:
    void use() const override {
        std::cout << "Using ConcreteProductA" << std::endl;
    }
};

// 派生类 ConcreteProductB
class ConcreteProductB : public Product {
public:
    void use() const override {
        std::cout << "Using ConcreteProductB" << std::endl;
    }
};

// 工厂类 Factory
class Factory {
public:
    enum class ProductType {
        ProductA,
        ProductB
    };

    std::unique_ptr<Product> createProduct(ProductType type) const {
        switch (type) {
            case ProductType::ProductA:
                return std::make_unique<ConcreteProductA>();
            case ProductType::ProductB:
                return std::make_unique<ConcreteProductB>();
            default:
                return nullptr;
        }
    }
};

// 客户端代码
int main() {
    Factory factory;

    // 创建产品A
    std::unique_ptr<Product> productA = factory.createProduct(Factory::ProductType::ProductA);
    if (productA) {
        productA->use();
    }

    // 创建产品B
    std::unique_ptr<Product> productB = factory.createProduct(Factory::ProductType::ProductB);
    if (productB) {
        productB->use();
    }

    return 0;
}
