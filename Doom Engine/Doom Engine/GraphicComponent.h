#pragma once
#include <memory>

class GraphicComponentSettings;

class GraphicComponent
{
	friend class Screen;
public:
	virtual ~GraphicComponent(void);

protected:
	
private:
	GraphicComponent(void);
	GraphicComponent(const GraphicComponent&);
	GraphicComponent(GraphicComponent&&);
	GraphicComponent& operator = (const GraphicComponent&);
	GraphicComponent& operator = (GraphicComponent&&);
	GraphicComponent(GraphicComponentSettings);

	void InjectParent(Screen*);
	void SetupRender(float, float);

	Screen* parentScreen;
	GraphicComponentSettings settings;
};

