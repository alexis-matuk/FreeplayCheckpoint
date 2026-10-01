/*
 * Copyright (c) 2021
 * All rights reserved.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "pch.h"
#include "CheckpointPlugin.h"

void CheckpointPlugin::writeSettingsFile() {
	std::ofstream setFile(gameWrapper->GetBakkesModPath() / "plugins" / "settings" / "checkpointplugin.set");
	setFile << R"(Freeplay Checkpoint
9|Bindings
9|Instructions: Enter Freeplay, HOLD button you wish to assign and click desired action button
9|Defaults: Saving Mode = Right Stick (R3), Replay Mode = Left Stick (L3).
9|Checkpoint Action = Back / Select / Share.
9|Rocket League's Reset Shot is suppressed while Saving or Replay Mode is active.
9|KBM players: bind cpt_ commands manually in Bakkesmod Bindings tab
8|
0|       Saving Mode (cpt_freeze)       |cpt_capture_key cpt_freeze
7|
9| [ $cpt_freeze_key$ ]
0| Replay Mode (cpt_replay_mode) |cpt_capture_key cpt_replay_mode
7|
9| [ $cpt_replay_mode_key$ ]
0|Checkpoint Action (cpt_do_checkpoint)|cpt_capture_key cpt_do_checkpoint
7|
9| [ $cpt_do_checkpoint_key$ ]
0|  Prev. Checkpoint (cpt_prev_checkpoint) |cpt_capture_key cpt_prev_checkpoint
7|
9| [ $cpt_prev_checkpoint_key$ ]
7|
1|Ignore While Playing##prev|cpt_ignore_prev
0|  Next Checkpoint (cpt_next_checkpoint) |cpt_capture_key cpt_next_checkpoint
7|
9| [ $cpt_next_checkpoint_key$ ]
7|
1|Ignore While Playing##next|cpt_ignore_next
0|Freeze Ball/Unfreeze Car (cpt_freeze_ball)|cpt_capture_key cpt_freeze_ball
7|
9| [ $cpt_freeze_ball_key$ ]
7|
1|Ignore While Playing##fb|cpt_ignore_freeze_ball
9|Previous and next enter Replay Mode while playing unless ignored above.
9|All replay controls remain disabled in Saving Mode.
9|
0|          Mirror shot (cpt_mirror_state)          |cpt_capture_key cpt_mirror_state
7|
9| [ $cpt_mirror_state_key$ ]
0|  Rewind & Fast Forward (cannot change)  |
7|
9| [ Steer Left & Right ]
9|
0|  Apply All Bindings  |cpt_apply_bindings
7|
9|(after updating or changing bindings)
7|
0| Remove Bindings  |cpt_remove_bindings
7|
9|:(
9|
0| Reset Default Bindings |cpt_reset_default_bindings
7|
9| (does not apply them)
9|
1|Disable binds in custom training|cpt_disable_training
1|Disable binds in workshop|cpt_disable_workshop
9|
9|Reset button loads last checkpoint instead of resetting if loaded before
5|(seconds)|cpt_load_after_reset|0|30
8|
9|
9|Variance - applied when leaving rewind mode
8|
5|Car Direction (degrees)|cpt_variance_car_dir|0|30
5|Car Speed (percent)|cpt_variance_car_spd|0|50
3|Car Rotation (strength)|cpt_variance_car_rot|0|10
5|Ball Direction (degrees)|cpt_variance_ball_dir|0|30
5|Ball Speed (percent)|cpt_variance_ball_spd|0|50
3|Ball Rotation (strength)|cpt_variance_ball_rot|0|10
5|Max. Total Variance|cpt_variance_tot|0|50
9|
1|Randomly mirror when loading checkpoint|cpt_mirror_loads
1|Load random checkpoint when entering Replay Mode|cpt_randomize_loads
8|
9|
9|Auto-reset checkpoint - reset when the following occurs:
8|
1|Goal Scored|cpt_reset_on_goal
1|Ball touches ground|cpt_reset_on_ball_ground
1|Load next checkpoint instead of resetting|cpt_next_instead_of_reset
8|
9|
9|Other options:
8|
9|Checkpoint Categories:
)";
	setFile << "6|Current Category|cpt_filename|" << getCategoryOptions() << "\n";
	setFile << R"(9|Shots in selected pack: $cpt_category_shot_count$
12|New Category Name|cpt_new_category
7|
0|Create and Select Category|cpt_create_category
9|
0|Delete Current Category|cpt_delete_category
7|
1|Move shots to Default and enable category deletion|cpt_allow_delete_category
9|
9|Move Current Checkpoint:
)";
	setFile << "6|Destination Category|cpt_move_category|" << getCategoryOptions(false) << "\n";
	setFile << R"(0|Move Current Checkpoint|cpt_move_checkpoint
9|
0|Delete ALL Shots (even locked shots; not undo-able!)|cpt_delete_all
7|
1|Enable Delete ALL Shots Button|cpt_allow_delete_all
9|
6|Boost when loading checkpoint|cpt_checkpoint_boost|Saved at checkpoint@saved&Unlimited@unlimited&Custom amount@custom
5|Custom checkpoint boost (%)|cpt_checkpoint_boost_custom|0|100
9|
1|Show player boost while rewinding|cpt_show_boost
1|Clean History -- Erases future history points when resuming|cpt_clean_history
5|History Length (seconds)|cpt_history_length|10|120
5|History Refresh Rate (ms)|cpt_snapshot_interval|1|10
9|
1|Debug -- Show debugging state|cpt_debug
9|
9|
9| Freeplay Checkpoint
9| Bugs/Feature Requests: github.com/NitrOP7674 -or- on Discord: https://discord.gg/SPBxrtfrZw
9| ** Please make sure to read the README first! **
)";
	setFile.close();
	cvarManager->executeCommand("cl_settings_refreshplugins");
}
