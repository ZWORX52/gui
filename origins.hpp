// NOLINT(legal/copyright)
#pragma once

#include <string>
#include <vector>

#include "./main.hpp"

namespace OriginsData {
enum PowerMode {
        PowerMode_None                          = 0,
        // Used by Power class to track what power type is currently set
        PowerMode_Normal                        = 1,    // TODO(ZWORX52)
        PowerMode_Action                        = 2,    // TODO(ZWORX52)
        PowerMode_Modify                        = 3,    // TODO(ZWORX52)
        PowerMode_Prevent                       = 4     // TODO(ZWORX52)
};

enum PowerType {
        PowerType_None                          = 0,
        // These todos are here because I haven't implemented those power types yet.
        // https://origins.readthedocs.io/en/latest/types/power_types/
        // Regular types
        PowerType_AttributeModifyTransfer       = 1,    // TODO(ZWORX52)
        PowerType_Attribute                     = 2,    // TODO(ZWORX52)
        PowerType_Burn                          = 3,    // TODO(ZWORX52)
        PowerType_Climbing                      = 4,    // TODO(ZWORX52)
        PowerType_ConditionedAttribute          = 5,    // TODO(ZWORX52)
        PowerType_ConditionedRestrictArmor      = 6,    // TODO(ZWORX52)
        PowerType_Cooldown                      = 7,    // TODO(ZWORX52)
        PowerType_CreativeFlight                = 8,    // TODO(ZWORX52)
        PowerType_DamageOverTime                = 9,    // TODO(ZWORX52)
        PowerType_DisableRegen                  = 10,   // TODO(ZWORX52)
        PowerType_EffectImmunity                = 11,   // TODO(ZWORX52)
        PowerType_ElytraFlight                  = 12,   // TODO(ZWORX52)
        PowerType_EntityGlow                    = 13,   // TODO(ZWORX52)
        PowerType_EntityGroup                   = 14,   // TODO(ZWORX52)
        PowerType_Exhaust                       = 15,   // TODO(ZWORX52)
        PowerType_FireImmunity                  = 16,   // TODO(ZWORX52)
        PowerType_FireProjectile                = 17,   // TODO(ZWORX52)
        PowerType_Freeze                        = 18,   // TODO(ZWORX52)
        PowerType_IgnoreWater                   = 19,   // TODO(ZWORX52)
        PowerType_Inventory                     = 20,   // TODO(ZWORX52)
        PowerType_Invisibility                  = 21,   // TODO(ZWORX52)
        PowerType_Invulnerability               = 22,   // TODO(ZWORX52)
        PowerType_ItemOnItem                    = 23,   // TODO(ZWORX52)
        PowerType_KeepInventory                 = 24,   // TODO(ZWORX52)
        PowerType_Launch                        = 25,   // TODO(ZWORX52)
        PowerType_LavaVision                    = 26,   // TODO(ZWORX52)
        PowerType_ModelColor                    = 27,   // TODO(ZWORX52)
        PowerType_Multiple                      = 28,   // TODO(ZWORX52)
        PowerType_NightVision                   = 29,   // TODO(ZWORX52)
        PowerType_Overlay                       = 30,   // TODO(ZWORX52)
        PowerType_Particle                      = 31,   // TODO(ZWORX52)
        PowerType_Phasing                       = 32,   // TODO(ZWORX52)
        PowerType_Recipe                        = 33,   // TODO(ZWORX52)
        PowerType_Resource                      = 34,   // TODO(ZWORX52)
        PowerType_RestrictArmor                 = 35,   // TODO(ZWORX52)
        PowerType_SelfGlow                      = 36,   // TODO(ZWORX52)
        PowerType_Shader                        = 37,   // TODO(ZWORX52)
        PowerType_Shaking                       = 38,   // TODO(ZWORX52)
        PowerType_Simple                        = 39,   // TODO(ZWORX52)
        PowerType_StackingStatusEffect          = 40,   // TODO(ZWORX52)
        PowerType_StartingEquipment             = 41,   // TODO(ZWORX52)
        PowerType_StatusBarTexture              = 42,   // TODO(ZWORX52)
        PowerType_Swimming                      = 43,   // TODO(ZWORX52)
        PowerType_ToggleNightVision             = 44,   // TODO(ZWORX52)
        PowerType_Toggle                        = 45,   // TODO(ZWORX52)
        PowerType_Tooltip                       = 46,   // TODO(ZWORX52)
        PowerType_WalkOnFluid                   = 47,   // TODO(ZWORX52)
};

enum ActionPowerType {
        ActionPowerType_None                    = 0,
        // Action-related
        PowerType_ActionOnBeingUsed             = 1,    // TODO(ZWORX52)
        PowerType_ActionOnBlockBreak            = 2,    // TODO(ZWORX52)
        PowerType_ActionOnBlockUse              = 3,    // TODO(ZWORX52)
        PowerType_ActionOnCallback              = 4,    // TODO(ZWORX52)
        PowerType_ActionOnEntityUse             = 5,    // TODO(ZWORX52)
        PowerType_ActionOnHit                   = 6,    // TODO(ZWORX52)
        PowerType_ActionOnItemUse               = 7,    // TODO(ZWORX52)
        PowerType_ActionOnLand                  = 8,    // TODO(ZWORX52)
        PowerType_ActionOnWakeUp                = 9,    // TODO(ZWORX52)
        PowerType_ActionOverTime                = 10,   // TODO(ZWORX52)
        PowerType_ActionWhenDamageTaken         = 11,   // TODO(ZWORX52)
        PowerType_ActionWhenHit                 = 12,   // TODO(ZWORX52)
        PowerType_ActiveSelf                    = 13,   // TODO(ZWORX52)
        PowerType_AttackerActionWhenHit         = 14,   // TODO(ZWORX52)
        PowerType_SelfActionOnHit               = 15,   // TODO(ZWORX52)
        PowerType_SelfActionOnKill              = 16,   // TODO(ZWORX52)
        PowerType_SelfActionWhenHit             = 17,   // TODO(ZWORX52)
        PowerType_TargetActionOnHit             = 18    // TODO(ZWORX52)
};

enum ModifyPowerType {
        ModifyPowerType_None                    = 0,
        // Modifying types
        ModifyPowerType_AirSpeed                = 1,    // TODO(ZWORX52)
        ModifyPowerType_BlockRender             = 2,    // TODO(ZWORX52)
        ModifyPowerType_BreakSpeed              = 3,    // TODO(ZWORX52)
        ModifyPowerType_CameraSubmersion        = 4,    // TODO(ZWORX52)
        ModifyPowerType_Crafting                = 5,    // TODO(ZWORX52)
        ModifyPowerType_DamageDealt             = 6,    // TODO(ZWORX52)
        ModifyPowerType_DamageTaken             = 7,    // TODO(ZWORX52)
        ModifyPowerType_Exhaustion              = 8,    // TODO(ZWORX52)
        ModifyPowerType_Falling                 = 9,    // TODO(ZWORX52)
        ModifyPowerType_FluidRender             = 10,   // TODO(ZWORX52)
        ModifyPowerType_Food                    = 11,   // TODO(ZWORX52)
        ModifyPowerType_Harvest                 = 12,   // TODO(ZWORX52)
        ModifyPowerType_Jump                    = 13,   // TODO(ZWORX52)
        ModifyPowerType_LavaSpeed               = 14,   // TODO(ZWORX52)
        ModifyPowerType_PlayerSpawn             = 15,   // TODO(ZWORX52)
        ModifyPowerType_ProjectileDamage        = 16,   // TODO(ZWORX52)
        ModifyPowerType_Slipperiness            = 17,   // TODO(ZWORX52)
        ModifyPowerType_StatusEffectAmplifier   = 18,   // TODO(ZWORX52)
        ModifyPowerType_StatusEffectDuration    = 19,   // TODO(ZWORX52)
        ModifyPowerType_SwimSpeed               = 20,   // TODO(ZWORX52)
        ModifyPowerType_XPGain                  = 21    // TODO(ZWORX52)
};

enum PreventPowerType {
        PreventPowerType_None                   = 0,
        // Preventing types
        PreventPowerType_BeingUsed              = 1,    // TODO(ZWORX52)
        PreventPowerType_BlockSelection         = 2,    // TODO(ZWORX52)
        PreventPowerType_BlockUse               = 3,    // TODO(ZWORX52)
        PreventPowerType_Death                  = 4,    // TODO(ZWORX52)
        PreventPowerType_ElytraFlight           = 5,    // TODO(ZWORX52)
        PreventPowerType_ElytraCollision        = 6,    // TODO(ZWORX52)
        PreventPowerType_EntityRender           = 7,    // TODO(ZWORX52)
        PreventPowerType_EntityUse              = 8,    // TODO(ZWORX52)
        PreventPowerType_FeatureRender          = 9,    // TODO(ZWORX52)
        PreventPowerType_GameEvent              = 10,   // TODO(ZWORX52)
        PreventPowerType_ItemUse                = 11,   // TODO(ZWORX52)
        PreventPowerType_Sleep                  = 12    // TODO(ZWORX52)
};

enum BiEntityActionType {
        BiEntityActionType_None                 = 0,
        // https://origins.readthedocs.io/en/latest/types/bientity_action_types/
        // Bi-entity
        BiEntityActionType_AddVelocity          = 1,    // TODO(ZWORX52)
        BiEntityActionType_Damage               = 2,    // TODO(ZWORX52)
        BiEntityActionType_Mount                = 3,    // TODO(ZWORX52)
        BiEntityActionType_SetInLove            = 4,    // TODO(ZWORX52)
        BiEntityActionType_Tame                 = 5,    // TODO(ZWORX52)
        // Bi-entity meta
        BiEntityActionType_ActorAction          = 6,    // TODO(ZWORX52)
        BiEntityActionType_Invert               = 7,    // TODO(ZWORX52)
        BiEntityActionType_TargetAction         = 8     // TODO(ZWORX52)
};

enum BlockActionType {
        BlockActionType_None                    = 0,
        // https://origins.readthedocs.io/en/latest/types/block_action_types/
        // Block
        BlockActionType_AddBlock                = 1,    // TODO(ZWORX52)
        BlockActionType_Bonemeal                = 2,    // TODO(ZWORX52)
        BlockActionType_ExecuteCommand          = 3,    // TODO(ZWORX52)
        BlockActionType_Explode                 = 4,    // TODO(ZWORX52)
        BlockActionType_ModifyBlockState        = 5,    // TODO(ZWORX52)
        BlockActionType_SetBlock                = 6,    // TODO(ZWORX52)
        // Block meta
        BlockActionType_Offset                  = 7     // TODO(ZWORX52)
};

enum EntityActionType {
        EntityActionType_None                   = 0,
        // https://origins.readthedocs.io/en/latest/types/entity_action_types/
        // Entity
        EntityActionType_AddVelocity            = 1,    // TODO(ZWORX52)
        EntityActionType_AddXP                  = 2,    // TODO(ZWORX52)
        EntityActionType_ApplyEffect            = 3,    // TODO(ZWORX52)
        EntityActionType_AreaOfEffect           = 4,    // TODO(ZWORX52)
        EntityActionType_BlockActionAt          = 5,    // TODO(ZWORX52)
        EntityActionType_ChangeResource         = 6,    // TODO(ZWORX52)
        EntityActionType_ClearEffect            = 7,    // TODO(ZWORX52)
        EntityActionType_CraftingTable          = 8,    // TODO(ZWORX52)
        EntityActionType_Damage                 = 9,    // TODO(ZWORX52)
        EntityActionType_Dismount               = 10,   // TODO(ZWORX52)
        EntityActionType_EmitGameEvent          = 11,   // TODO(ZWORX52)
        EntityActionType_EnderChest             = 12,   // TODO(ZWORX52)
        EntityActionType_EquippedItemAction     = 13,   // TODO(ZWORX52)
        EntityActionType_ExecuteCommand         = 14,   // TODO(ZWORX52)
        EntityActionType_Exhaust                = 15,   // TODO(ZWORX52)
        EntityActionType_Explode                = 16,   // TODO(ZWORX52)
        EntityActionType_Extinguish             = 17,   // TODO(ZWORX52)
        EntityActionType_Feed                   = 18,   // TODO(ZWORX52)
        EntityActionType_GainAir                = 19,   // TODO(ZWORX52)
        EntityActionType_Give                   = 20,   // TODO(ZWORX52)
        EntityActionType_GrantPower             = 21,   // TODO(ZWORX52)
        EntityActionType_Heal                   = 22,   // TODO(ZWORX52)
        EntityActionType_PassengerAction        = 23,   // TODO(ZWORX52)
        EntityActionType_PlaySound              = 24,   // TODO(ZWORX52)
        EntityActionType_Raycast                = 25,   // TODO(ZWORX52)
        EntityActionType_RevokePower            = 26,   // TODO(ZWORX52)
        EntityActionType_RidingAction           = 27,   // TODO(ZWORX52)
        EntityActionType_SetFallDistance        = 28,   // TODO(ZWORX52)
        EntityActionType_SetOnFire              = 29,   // TODO(ZWORX52)
        EntityActionType_SpawnEffectCloud       = 30,   // TODO(ZWORX52)
        EntityActionType_SpawnEntity            = 31,   // TODO(ZWORX52)
        EntityActionType_SpawnParticles         = 32,   // TODO(ZWORX52)
        EntityActionType_SwingHand              = 33,   // TODO(ZWORX52)
        EntityActionType_Toggle                 = 34,   // TODO(ZWORX52)
        EntityActionType_TriggerCooldown        = 35    // TODO(ZWORX52)
};

enum ItemActionType {
        ItemActionType_None                     = 0,
        // https://origins.readthedocs.io/en/latest/types/item_action_types/
        // Item
        ItemActionType_Consume                  = 1,    // TODO(ZWORX52)
        ItemActionType_Damage                   = 2,    // TODO(ZWORX52)
        ItemActionType_Modify                   = 3     // TODO(ZWORX52)
};

enum MetaActionType {
        MetaActionType_None                     = 0,
        // https://origins.readthedocs.io/en/latest/types/meta_action_types/
        // Meta
        MetaActionType_And                      = 1,    // TODO(ZWORX52)
        MetaActionType_Chance                   = 2,    // TODO(ZWORX52)
        MetaActionType_Choice                   = 3,    // TODO(ZWORX52)
        MetaActionType_Delay                    = 4,    // TODO(ZWORX52)
        MetaActionType_IfElseList               = 5,    // TODO(ZWORX52)
        MetaActionType_IfElse                   = 6,    // TODO(ZWORX52)
        MetaActionType_Nothing                  = 7     // TODO(ZWORX52)
};

enum ConditionMode {
        ConditionMode_None                      = 0,    // TODO(ZWORX52)
        ConditionMode_BiEntity                  = 1,    // TODO(ZWORX52)
        ConditionMode_Biome                     = 2,    // TODO(ZWORX52)
        ConditionMode_Block                     = 3,    // TODO(ZWORX52)
        ConditionMode_Damage                    = 4,    // TODO(ZWORX52)
        ConditionMode_Entity                    = 5,    // TODO(ZWORX52)
        ConditionMode_Fluid                     = 6,    // TODO(ZWORX52)
        ConditionMode_Item                      = 7,    // TODO(ZWORX52)
        ConditionMode_Meta                      = 8     // TODO(ZWORX52)
};

enum BiEntityConditionType {
        BiEntityConditionType_None              = 0,
        // https://origins.readthedocs.io/en/latest/types/bientity_condition_types/
        // Bi-entity
        BiEntityConditionType_AttackTarget      = 1,    // TODO(ZWORX52)
        BiEntityConditionType_Attacker          = 2,    // TODO(ZWORX52)
        BiEntityConditionType_CanSee            = 3,    // TODO(ZWORX52)
        BiEntityConditionType_Distance          = 4,    // TODO(ZWORX52)
        BiEntityConditionType_Owner             = 5,    // TODO(ZWORX52)
        BiEntityConditionType_RelativeRotation  = 6,    // TODO(ZWORX52)
        BiEntityConditionType_RidingRecursive   = 7,    // TODO(ZWORX52)
        BiEntityConditionType_RidingRoot        = 8,    // TODO(ZWORX52)
        // Meta
        BiEntityConditionType_ActorCondition    = 10,   // TODO(ZWORX52)
        BiEntityConditionType_Both              = 11,   // TODO(ZWORX52)
        BiEntityConditionType_Either            = 12,   // TODO(ZWORX52)
        BiEntityConditionType_Invert            = 13,   // TODO(ZWORX52)
        BiEntityConditionType_TargetCondition   = 14,   // TODO(ZWORX52)
        BiEntityConditionType_Undirected        = 15,   // TODO(ZWORX52)
};

enum BiomeConditionType {
        BiomeConditionType_None                 = 0,
        // https://origins.readthedocs.io/en/latest/types/biome_condition_types/
        // Biome
        BiomeConditionType_Category             = 1,    // TODO(ZWORX52)
        BiomeConditionType_HighHumidity         = 2,    // TODO(ZWORX52)
        BiomeConditionType_Precipitation        = 3,    // TODO(ZWORX52)
        BiomeConditionType_Temperature          = 4     // TODO(ZWORX52)
};

enum BlockConditionType {
        BlockConditionType_None                 = 0,
        // https://origins.readthedocs.io/en/latest/types/block_condition_types/
        // Block
        BlockConditionType_Adjacent             = 1,    // TODO(ZWORX52)
        BlockConditionType_Attachable           = 2,    // TODO(ZWORX52)
        BlockConditionType_BlastResistance      = 3,    // TODO(ZWORX52)
        BlockConditionType_BlockState           = 4,    // TODO(ZWORX52)
        BlockConditionType_Block                = 5,    // TODO(ZWORX52)
        BlockConditionType_DistanceFromCoordinates = 6,  // TODO(ZWORX52)
        BlockConditionType_ExposedToSky         = 7,    // TODO(ZWORX52)
        BlockConditionType_Fluid                = 8,    // TODO(ZWORX52)
        BlockConditionType_Hardness             = 9,    // TODO(ZWORX52)
        BlockConditionType_Height               = 10,   // TODO(ZWORX52)
        BlockConditionType_InTag                = 11,   // TODO(ZWORX52)
        BlockConditionType_LightBlocking        = 12,   // TODO(ZWORX52)
        BlockConditionType_LightLevel           = 13,   // TODO(ZWORX52)
        BlockConditionType_Material             = 14,   // TODO(ZWORX52)
        BlockConditionType_MovementBlocking     = 15,   // TODO(ZWORX52)
        BlockConditionType_NBT                  = 16,   // TODO(ZWORX52)
        BlockConditionType_Replacable           = 17,   // TODO(ZWORX52)
        BlockConditionType_Slipperiness         = 18,   // TODO(ZWORX52)
        BlockConditionType_Waterloggable        = 19,   // TODO(ZWORX52)
        // Meta
        BlockConditionType_Offset               = 20    // TODO(ZWORX52)
};

enum DamageConditionType {
        DamageConditionType_None                = 0,
        // https://origins.readthedocs.io/en/latest/types/damage_condition_types/
        // Damage
        DamageConditionType_Amount              = 1,    // TODO(ZWORX52)
        DamageConditionType_Attacker            = 2,    // TODO(ZWORX52)
        DamageConditionType_Fire                = 3,    // TODO(ZWORX52)
        DamageConditionType_Name                = 4,    // TODO(ZWORX52)
        DamageConditionType_Projectile          = 5     // TODO(ZWORX52)
};

enum EntityConditionType {
        EntityConditionType_None                = 0,
        // https://origins.readthedocs.io/en/latest/types/entity_condition_types/
        // Entity
        EntityConditionType_Ability             = 1,    // TODO(ZWORX52)
        EntityConditionType_Advancement         = 2,    // TODO(ZWORX52)
        EntityConditionType_Air                 = 3,    // TODO(ZWORX52)
        EntityConditionType_Attribute           = 4,    // TODO(ZWORX52)
        EntityConditionType_Biome               = 5,    // TODO(ZWORX52)
        EntityConditionType_BlockCollision      = 6,    // TODO(ZWORX52)
        EntityConditionType_BlockInRadius       = 7,    // TODO(ZWORX52)
        EntityConditionType_Brightness          = 8,    // TODO(ZWORX52)
        EntityConditionType_Climbing            = 9,    // TODO(ZWORX52)
        EntityConditionType_CollidedHorizontally = 10,  // TODO(ZWORX52)
        EntityConditionType_Command             = 11,   // TODO(ZWORX52)
        EntityConditionType_CreativeFlying      = 12,   // TODO(ZWORX52)
        EntityConditionType_Daytime             = 13,   // TODO(ZWORX52)
        EntityConditionType_Dimension           = 14,   // TODO(ZWORX52)
        EntityConditionType_DistanceFromCoordinates = 15,  // TODO(ZWORX52)
        EntityConditionType_ElytraFlightPossible = 16,  // TODO(ZWORX52)
        EntityConditionType_Enchantment         = 17,   // TODO(ZWORX52)
        EntityConditionType_EntityGroup         = 18,   // TODO(ZWORX52)
        EntityConditionType_EntityType          = 19,   // TODO(ZWORX52)
        EntityConditionType_EquippedItem        = 20,   // TODO(ZWORX52)
        EntityConditionType_Exists              = 21,   // TODO(ZWORX52)
        EntityConditionType_ExposedToSky        = 22,   // TODO(ZWORX52)
        EntityConditionType_ExposedToSun        = 23,   // TODO(ZWORX52)
        EntityConditionType_FallDistance        = 24,   // TODO(ZWORX52)
        EntityConditionType_FallFlying          = 25,   // TODO(ZWORX52)
        EntityConditionType_FluidHeight         = 26,   // TODO(ZWORX52)
        EntityConditionType_FoodLevel           = 27,   // TODO(ZWORX52)
        EntityConditionType_Gamemode            = 28,   // TODO(ZWORX52)
        EntityConditionType_Health              = 29,   // TODO(ZWORX52)
        EntityConditionType_InBlockAnywhere     = 30,   // TODO(ZWORX52)
        EntityConditionType_InBlock             = 31,   // TODO(ZWORX52)
        EntityConditionType_InRain              = 32,   // TODO(ZWORX52)
        EntityConditionType_InTag               = 33,   // TODO(ZWORX52)
        EntityConditionType_Invisible           = 34,   // TODO(ZWORX52)
        EntityConditionType_Living              = 35,   // TODO(ZWORX52)
        EntityConditionType_Moving              = 36,   // TODO(ZWORX52)
        EntityConditionType_NBT                 = 37,   // TODO(ZWORX52)
        EntityConditionType_OnBlock             = 38,   // TODO(ZWORX52)
        EntityConditionType_OnFire              = 39,   // TODO(ZWORX52)
        EntityConditionType_Origin              = 40,   // TODO(ZWORX52)
        EntityConditionType_PassengerRecursive  = 41,   // TODO(ZWORX52)
        EntityConditionType_Passenger           = 42,   // TODO(ZWORX52)
        EntityConditionType_PowerActive         = 43,   // TODO(ZWORX52)
        EntityConditionType_PowerType           = 44,   // TODO(ZWORX52)
        EntityConditionType_Power               = 45,   // TODO(ZWORX52)
        EntityConditionType_Predicate           = 46,   // TODO(ZWORX52)
        EntityConditionType_Raycast             = 47,   // TODO(ZWORX52)
        EntityConditionType_RelativeHealth      = 48,   // TODO(ZWORX52)
        EntityConditionType_Resource            = 49,   // TODO(ZWORX52)
        EntityConditionType_RidingRecursive     = 50,   // TODO(ZWORX52)
        EntityConditionType_RidingRoot          = 51,   // TODO(ZWORX52)
        EntityConditionType_Riding              = 52,   // TODO(ZWORX52)
        EntityConditionType_SaturationLevel     = 53,   // TODO(ZWORX52)
        EntityConditionType_Scoreboard          = 54,   // TODO(ZWORX52)
        EntityConditionType_Sneaking            = 55,   // TODO(ZWORX52)
        EntityConditionType_Sprinting           = 56,   // TODO(ZWORX52)
        EntityConditionType_StatusEffect        = 57,   // TODO(ZWORX52)
        EntityConditionType_SubmergedIn         = 58,   // TODO(ZWORX52)
        EntityConditionType_Swimming            = 59,   // TODO(ZWORX52)
        EntityConditionType_Tamed               = 60,   // TODO(ZWORX52)
        EntityConditionType_TimeOfDay           = 61,   // TODO(ZWORX52)
        EntityConditionType_UsingEffectiveTool  = 62,   // TODO(ZWORX52)
        EntityConditionType_UsingItem           = 63,   // TODO(ZWORX52)
        EntityConditionType_XPLevels            = 64,   // TODO(ZWORX52)
        EntityConditionType_XPPoints            = 65    // TODO(ZWORX52)
};

enum FluidConditionType {
        FluidConditionType_None                 = 0,
        // https://origins.readthedocs.io/en/latest/types/fluid_condition_types/
        // Fluid
        FluidConditionType_Empty                = 1,    // TODO(ZWORX52)
        FluidConditionType_InTag                = 2,    // TODO(ZWORX52)
        FluidConditionType_Still                = 3     // TODO(ZWORX52)
};

enum ItemConditionType {
        ItemConditionType_None                  = 0,
        // https://origins.readthedocs.io/en/latest/types/item_condition_types/
        // Item
        ItemConditionType_Amount                = 1,    // TODO(ZWORX52)
        ItemConditionType_ArmorValue            = 2,    // TODO(ZWORX52)
        ItemConditionType_Empty                 = 3,    // TODO(ZWORX52)
        ItemConditionType_Enchantment           = 4,    // TODO(ZWORX52)
        ItemConditionType_Fireproof             = 5,    // TODO(ZWORX52)
        ItemConditionType_Food                  = 6,    // TODO(ZWORX52)
        ItemConditionType_HarvestLevel          = 7,    // TODO(ZWORX52)
        ItemConditionType_Ingredient            = 8,    // TODO(ZWORX52)
        ItemConditionType_Meat                  = 9,    // TODO(ZWORX52)
        ItemConditionType_NBT                   = 10,   // TODO(ZWORX52)
        ItemConditionType_Smeltable             = 11    // TODO(ZWORX52)
};

enum MetaConditionType {
        MetaConditionType_None                  = 0,
        // https://origins.readthedocs.io/en/latest/types/meta_condition_types/
        // Meta
        MetaConditionType_And                   = 1,    // TODO(ZWORX52)
        MetaConditionType_Constant              = 2,    // TODO(ZWORX52)
        MetaConditionType_Not                   = 3,    // TODO(ZWORX52)
        MetaConditionType_Or                    = 4     // TODO(ZWORX52)
};

class Condition {
 public:
        ConditionMode mode;

        BiEntityConditionType bientity_condition;
        BiomeConditionType biome_condition;
        BlockConditionType block_condition;
        DamageConditionType damage_condition;
        EntityConditionType entity_condition;
        FluidConditionType fluid_condition;
        ItemConditionType item_condition;
        MetaConditionType meta_condition;

        bool Verify();  // Check if it's a valid condition, i.e. if only one condition is set.

        // Sets condition to the specified condition, None-ing other conditions along the way.
        void SetCondition(int, ConditionMode);

        Condition();
};

class Power {
 public:
        PowerMode mode;

        PowerType normal_type;
        ActionPowerType action_type;
        ModifyPowerType modify_type;
        PreventPowerType prevent_type;

        Condition condition;

        void SetPower(int, PowerMode);

        Power();
};

class Origin {
 public:
        std::vector<Power> powers;
};

class Layer {
 public:
        std::vector<Origin> origins;
        std::string layer_name;

        Layer();
};

class Datapack {
 public:
        Layer layer;  // Because most (read: all) datapacks just add to the origins layer.
        // Support for more layers to be added.
        std::string filename;

        Datapack();

        bool Save();
};

// int represents a power type, as "PowerType type" is synonymous to "int type"
const char *PowerToString(int type, PowerMode mode);
void LoadFile(std::string filename, std::vector<Datapack> *datapack_list);
}  // namespace OriginsData

