############################################设计模式############################################################

##########################################创建行为模式###########################################################

# 工厂模式
add_executable(factory_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/factoryPattern/main.cpp
        ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/factoryPattern/cameraFactory.hpp
        ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/factoryPattern/canonCamera.hpp
        ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/factoryPattern/nikonCamera.hpp
        ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/factoryPattern/sonyCamera.hpp)

# 抽象工厂
file(GLOB_RECURSE ABSTRACT_FACTORY_SOURCE_FILES ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/abstractFactoryPattern/*.hpp)

add_executable(abstract_factory_pattern
        ${ABSTRACT_FACTORY_SOURCE_FILES}
        ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/abstractFactoryPattern/main.cpp)

# 单例模式模式

##饿汉模式
file(GLOB_RECURSE HUNGRY_MAN_SINGLETON_SOURCE_FILES ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/singletonPattern/hungryMan/*.hpp)

add_executable(hungry_man_singleton
        ${HUNGRY_MAN_SINGLETON_SOURCE_FILES}
        ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/singletonPattern/hungryMan/main.cpp)

#懒汉模式
file(GLOB_RECURSE LAZYBONES_SINGLETON_SOURCE_FILES ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/singletonPattern/lazybones/*.hpp)

add_executable(lazybones_singleton
        ${LAZYBONES_SINGLETON_SOURCE_FILES}
        ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/singletonPattern/lazybones/main.cpp)

# 构建者模式
add_executable(build_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/builderPattern/main.cpp)

# 原型模式( 拷贝模式 )
add_executable(prototype_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/creationPattern/prototypePattern/main.cpp)

##########################################结构型模式###########################################################

# 改造者(适配器)模式
add_executable(adapter_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/structuralPattern/adapterPattern/main.cpp)

# 桥接模式模式
add_executable(bridge_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/structuralPattern/bridgePattern/main.cpp)

# 过滤器模式（Filter Pattern）或标准模式（Criteria Pattern）
add_executable(filter_criteria_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/structuralPattern/filterAndCriteriaPattern/main.cpp)

# 组合模式
add_executable(component_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/structuralPattern/componentPattern/main.cpp)

# 装饰器模式
add_executable(decorator_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/structuralPattern/decoratorPattern/main.cpp)

# 享元模式
add_executable(flyweight_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/structuralPattern/flyweightPattern/main.cpp)

# 代理模式
add_executable(proxy_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/structuralPattern/proxyPattern/main.cpp)

##########################################行为型模式###########################################################

# 责任链模式
add_executable(chainOfResponsibility_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/chainOfResponsibilityPattern/main.cpp)

# 命令模式
add_executable(command_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/commandPattern/main.cpp)

# 解释器模式
add_executable(interpreter_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/interpreterPattern/main.cpp)

# 迭代器模式
add_executable(iterator_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/iteratorPattern/main.cpp)

# 中介者模式
add_executable(mediator_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/mediatorPattern/main.cpp)

# 备忘录模式
add_executable(memento_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/mementoPattern/main.cpp)

# 观察者模式
add_executable(observer_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/observerPattern/main.cpp)

# 状态模式
add_executable(state_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/statePattern/main.cpp)

# 空对象模式
add_executable(null_object_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/nullObjectPattern/main.cpp)

# 策略模式
add_executable(strategy_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/strategyPattern/main.cpp)

# 模板模式
add_executable(template_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/templatePattern/main.cpp)

# 访问者模式
add_executable(visitor_pattern
        ${CMAKE_SOURCE_DIR}/examples/designPattern/behavioralPattern/visitorPattern/main.cpp)
