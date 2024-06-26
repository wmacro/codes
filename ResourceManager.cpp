#include <iostream>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <shared_mutex>

// 资源管理池模板类
template <typename IDType, typename ResourceType>
class ResourceManager {
public:
    // 获取资源，如果不存在则创建
    std::shared_ptr<ResourceType> getResource(const IDType& id) {
        {
            // 先使用共享锁检查资源是否存在
            std::shared_lock<std::shared_mutex> readLock(mutex_);
            auto it = resources_.find(id);
            if (it != resources_.end()) {
                return it->second;
            }
        }

        // 资源不存在，升级为独占锁并创建资源
        std::unique_lock<std::shared_mutex> writeLock(mutex_);
        auto it = resources_.find(id);
        if (it == resources_.end()) {
            std::shared_ptr<ResourceType> resource = std::make_shared<ResourceType>(id);
            resources_[id] = resource;
            return resource;
        } else {
            return it->second;
        }
    }

private:
    std::unordered_map<IDType, std::shared_ptr<ResourceType>> resources_;
    mutable std::shared_mutex mutex_;
};

// 示例资源类
class Resource {
public:
    Resource(int id) : id_(id) {
        std::cout << "Resource " << id_ << " created." << std::endl;
    }
    ~Resource() {
        std::cout << "Resource " << id_ << " destroyed." << std::endl;
    }

    int getId() const { return id_; }

private:
    int id_;
};

// 示例使用
int main() {
    ResourceManager<int, Resource> manager;

    auto res1 = manager.getResource(1);
    auto res2 = manager.getResource(2);
    auto res3 = manager.getResource(1);  // 应该返回已创建的资源

    std::cout << "Resource 1 ID: " << res1->getId() << std::endl;
    std::cout << "Resource 2 ID: " << res2->getId() << std::endl;
    std::cout << "Resource 3 ID: " << res3->getId() << std::endl;

    return 0;
}
