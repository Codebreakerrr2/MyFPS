#pragma once
#include <functional>
namespace Factory{

//----------------------------------SHADER FACTORY LAMDAS----------------------------//
//Mock SHADER test Factory
inline auto mockShader = []()->std::unique_ptr<SHADER::IShader> {
    return std::make_unique<SHADER::shaderMock>();
};

}
