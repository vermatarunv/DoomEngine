#include "GraphicComponent.h"
#include "GraphicComponentSettings.h"

GraphicComponent::~GraphicComponent(void)
{
}


GraphicComponent::GraphicComponent(GraphicComponentSettings _settings)
{
	settings = _settings;
}
void InjectParent(Screen*);
void SetupRender(float, float);