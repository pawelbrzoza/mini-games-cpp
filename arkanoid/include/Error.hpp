#pragma once

class Error
{
public:
    virtual void error(const std::string) = 0;
    virtual ~Error() {};
};