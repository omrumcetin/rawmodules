#pragma once

class application
{
public:
    inline application() { };
    inline virtual ~application() { };
    inline virtual void initialize() {};
    inline virtual void update(float DeltaTime) {};
    inline virtual void render(float AspectRatio) {};
    inline virtual void shutdown() {};
private:
    application(const application&);
    application& operator=(const application&);
};

