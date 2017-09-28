#pragma once

#include "game/state/stateobject.h"
#include "game/ui/tileview/citytileview.h"
#include "library/sp.h"
#include <map>
#include <vector>

namespace OpenApoc
{

class Form;
class GameState;
class GraphicButton;
class Control;
class Vehicle;
class Sample;
class Base;
class Building;
class Organisation;
class VehicleTileInfo;

enum class UpdateSpeed
{
	Pause,
	Speed1,
	Speed2,
	Speed3,
	Speed4,
	Speed5,
};

enum class CityIcon
{
	UnselectedFrame,
	SelectedFrame,
	SelectedSecondaryFrame,

	InBase,
	InVehicle,
	InBuilding,
	InMotion,
};


enum class SelectionState
{
	Normal,
	VehicleGotoBuilding,
	VehicleGotoLocation,
	VehicleAttackVehicle,
	VehicleAttackBuilding,
};

class CityView : public CityTileView
{
  private:
	sp<Form> activeTab, baseForm;
	std::vector<sp<Form>> uiTabs;
	sp<Form> overlayTab;
	std::vector<sp<GraphicButton>> miniViews;
	UpdateSpeed updateSpeed;
	UpdateSpeed lastSpeed;

	sp<GameState> state;

	std::map<sp<Vehicle>, std::pair<VehicleTileInfo, sp<Control>>> vehicleListControls;

	bool followVehicle;

	void updateSelectedUnits();

	SelectionState selectionState;
	bool modifierLShift = false;
	bool modifierRShift = false;
	bool modifierLAlt = false;
	bool modifierRAlt = false;
	bool modifierLCtrl = false;
	bool modifierRCtrl = false;

	sp<Palette> day_palette;
	sp<Palette> twilight_palette;
	sp<Palette> night_palette;

	bool colorForward = true;
	int colorCurrent = 0;

	std::vector<sp<Palette>> mod_day_palette;
	std::vector<sp<Palette>> mod_twilight_palette;
	std::vector<sp<Palette>> mod_night_palette;

	bool drawCity = true;
	sp<Surface> surface;

	// Orders

	void orderGoToBase();
	void orderMove(Vec3<float> position, bool useTeleporter);
	void orderMove(StateRef<Building> building, bool useTeleporter);
	void orderSelect(StateRef<Vehicle> vehicle, bool inverse, bool additive);
	void orderAttack(StateRef<Vehicle> vehicle);
	void orderAttack(StateRef<Building> building);

  public:
	CityView(sp<GameState> state);
	~CityView() override;

	void initiateDefenseMission(StateRef<Base> base, StateRef<Organisation> attacker);

	void begin() override;
	void resume() override;
	void update() override;
	void render() override;
	void eventOccurred(Event *e) override;
	bool handleKeyDown(Event *e);
	bool handleKeyUp(Event *e);
	bool handleMouseDown(Event *e);
	bool handleGameStateEvent(Event *e);

	void setUpdateSpeed(UpdateSpeed updateSpeed);
	void zoomLastEvent();
	void setSelectionState(SelectionState selectionState);
};

}; // namespace OpenApoc
