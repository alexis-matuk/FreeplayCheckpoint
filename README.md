# Freeplay Checkpoint
### Rewind, Save, and Restore Checkpoints in Freeplay, Replays, and Custom Training!
<p align="center"><img src="banner.png" width="350"></p>

## Enhancements in This Version

This version extends the original Freeplay Checkpoint implementation with:

- **Checkpoint boost modes**:
  - Restore the boost amount saved with the checkpoint.
  - Keep unlimited boost while replaying a checkpoint.
  - Start each replay with a custom boost percentage.
- **Checkpoint categories**:
  - Create and select named categories backed by separate checkpoint files.
  - See the number of shots in the selected category directly in plugin settings.
  - Move individual checkpoints between categories while preserving their lock state.
  - Delete a category while safely moving all of its checkpoints to **Default**.
  - Browse and replay every saved checkpoint through the virtual, read-only **All**
    category.
- **Dedicated checkpoint modes**:
  - Use **R3** for checkpoint saving and **L3** for checkpoint replay selection.
  - Keep navigation, mirroring, locking, and deletion disabled while saving.
  - Ignore vertical stick movement while rewinding so accidental input does not
    exit Saving Mode.
  - Suppress Rocket League's native Reset Shot while a checkpoint mode owns the
    shared action button.
- **Improved Freeplay and replay overlays**:
  - Display the source category and current checkpoint counter without overflowing
    the screen.
  - Show separate **Checkpoint Saving** and **Checkpoint Replay** control references
    using the configured controller bindings.
  - Show the selected category and replay-saving controls while viewing a replay.
  - Keep checkpoint overlays hidden outside standard Freeplay and Rocket League replays.
- **Replay checkpoint capture**:
  - Enter Replay Saving Mode with **R3** and save the current replay frame to the
    selected category.
  - Disable checkpoint playback, navigation, deletion, and plugin rewind controls
    while viewing a replay.
- **Simplified local development**:
  - Build, install, and reload the plugin using the included `build.ps1` script.

**Setup:**

1. Open bakkesmod window (F2 by default)
2. Click "Plugins"
3. Find "Freeplay Checkpoint" in the plugin list on the left.
4. Optional: choose new button bindings.
5. Click **Apply All Bindings**, especially after upgrading or changing a binding.

Alternatively, or for KBM users: assign the `cpt_` commands (listed in the Command
Reference section below) as desired in the "Bindings" tab.

It is recommended to disable goal scoring in bakkesmod while using this plugin.

**Building and Installing:**

From PowerShell in the repository root, run:

```powershell
.\build.ps1
```

The script builds the Release x64 plugin and runs the project's BakkesMod post-build
patcher, which installs and reloads the plugin.

**Basic Usage:**

Note: assumes default bindings from above.

1. Start freeplay mode. Set up a shot.
2. Press **Right Stick (R3)** to enter **Checkpoint Saving Mode**.
3. Steer left/right to rewind/advance time, then press **Back / Select / Share**
   to save the selected state.
   - Vertical stick movement is ignored so accidental up/down input cannot exit
     Saving Mode while rewinding.
   - Replay navigation, mirroring, and deletion are disabled in Saving Mode.
4. Resume driving, then press **Left Stick (L3)** to enter **Checkpoint Replay Mode**
   and load the current saved checkpoint.
   - D-pad left/right also enter Replay Mode unless their **Ignore While Playing**
     options are enabled.
5. In Replay Mode:
   - Press left/right on the d-pad to change checkpoints.
   - Press down on the d-pad to mirror the selected checkpoint.
   - Press up on the d-pad to unfreeze the car while keeping the ball frozen.
   - Press **Back / Select / Share** twice to delete the selected checkpoint.
   - Use throttle, jump, or boost to leave Replay Mode and play the shot.

**Saving Checkpoints from a Replay:**

1. Open a Rocket League replay and use the game's replay controls to choose a frame.
2. Press **Right Stick (R3)** to enter **Replay Saving Mode**.
3. Confirm the selected checkpoint category in the on-screen panel.
4. Press **Back / Select / Share** to save the current replay frame.

Only Replay Saving Mode and its save action are available in a replay. L3, checkpoint
navigation, mirroring, deletion, and the plugin's rewind/fast-forward controls remain
disabled. Press R3 again to cancel Replay Saving Mode without saving.

**In-Game Controller Bindings Tip:**
Rocket League may assign **R3**, **L3**, or **Select / Back / Share** to another
Freeplay action. Native **Reset Shot** events are ignored while Checkpoint Saving
Mode or Checkpoint Replay Mode is active, so sharing the checkpoint action button
does not exit the active mode. Other conflicting native actions may still need to
be moved in **Options -> Controls -> View/Change Bindings**.

**Command Reference:**

- `cpt_freeze`: activates Checkpoint Saving Mode in Freeplay or toggles Replay
  Saving Mode while viewing a replay
- `cpt_replay_mode`: activates Checkpoint Replay Mode and loads the current checkpoint
- `cpt_do_checkpoint`:
  - In Saving Mode: saves the selected state as a checkpoint
  - In Replay Mode: deletes the current checkpoint (press twice)
  - In a Rocket League replay: saves the currently selected car and ball only
    while Replay Saving Mode is active
- `cpt_prev_checkpoint` / `cpt_next_checkpoint`: loads the previous/next checkpoint
  while in Replay Mode
- `cpt_rand_checkpoint`: loads a random saved checkpoint
- `cpt_lock_checkpoint`: locks/unlocks the current checkpoint to prevent/allow its deletion.
- `cpt_mirror_state`: mirrors the selected shot while in Replay Mode.
- `cpt_freeze_ball`:
  - In Replay Mode: unfreezes the player's car while keeping the ball frozen
- `cpt_copy`\*:
  - In rewind mode: copy the current state to the clipboard
  - While playing: copy the last loaded checkpoint or quick checkpoint to the clipboard
  - In a replay: copy the currently selected car & ball to the clipboard
- `cpt_paste`\*: load a checkpoint from the clipboard as a quick checkpoint

\* - The `cpt_copy` and `cpt_paste` commands can be entered in the F6 console of bakkesmod.

**Settings Reference:**

- **Bindings**:
  - KBM players should manually bind the cpt_ keys in the bindings section.
  - Controller players may hold the button they wish to bind and click the action they
    wish to bind to that button.
  - Saving Mode defaults to **R3** and Replay Mode defaults to **L3**.
  - **Ignore While Playing** can disable previous, next, and freeze-ball actions
    until a mode is active.
  - Previous and next enter Replay Mode when used while playing unless ignored.
  - Replay controls are always disabled while Saving Mode is active.
  - Do *not* bind plugin actions to conflicting Rocket League controls.
  - Disable binds in custom training: ignore commands in custom training
  - Disable binds in workshop: ignore commands on workshop maps
  - Reset button loads last checkpoint instead of resetting:
    - If a checkpoint was loaded within the last few seconds (set by this amount),
      the reset shot button will load that checkpoint instead of resetting training.
- **Variance**:
  - When resuming play from frozen, apply randomness to the scenario.
  - **Randomly mirror when loading checkpoint**:
    - Randomly mirrors shots when loading to practice opposite angles.
  - **Load random checkpoint**:
    - When Replay Mode starts, load a random checkpoint instead of the current one.
- **Auto-reset checkpoint**:
  - Allows drilling a shot or running through shots like a training pack.
- **Other Options**:
  - **Checkpoint Categories**:
    - Select a category to load its saved shots. New checkpoints are saved to the
      currently selected category.
    - **All** is a read-only combined view of every checkpoint in every category.
      Select a specific category before saving, deleting, or changing a lock.
    - Enter a category name and click **Create and Select Category** to create an
      independent checkpoint file.
    - Enable category deletion and click **Delete Current Category** to move all
      of its checkpoints to **Default**, then remove the category.
    - Select a destination and click **Move Current Checkpoint** to move the
      currently selected shot, including its locked state, into another category.
    - The existing `cpt_filename` value remains compatible when upgrading.
    - The active category is displayed beside the current checkpoint number.
    - Plugin settings show the number of shots in the selected category or combined
      **All** view.
  - **Boost when loading checkpoint**:
    - **Saved at checkpoint** restores the boost amount captured with the checkpoint.
    - **Unlimited** keeps boost full while playing from the checkpoint.
    - **Custom amount** restores the selected boost percentage each time the checkpoint loads.
  - **Delete ALL Shots**:
    - Deletes every saved checkpoint in the current file, even locked shots.  Check the
      "Enable" checkbox first to enable the button - there is no warning or confirmation
      once this is checked.
  - **Show player boost while rewinding**:
    - If set, boost will be shown when rewinding if the player was boosting while recording.
      Does not affect checkpoints.
  - **Clean History**:
    - When rewinding and restoring an old state, deletes history after that restored point.
  - **History Length**: amount of history to save
  - **History Refresh Rate**:
    - Interval between saved state points.  Set small for maximum smoothness in history data,
      but at the possible expense of worse performance.
  - **Debug**:
    - Shows some additional debugging data.  Probably not useful.
    
**Other CVars**
- `cpt_car_frozen`/`cpt_ball_frozen`:
  - These are set by this plugin whenever the car or ball or both are frozen in freeplay.

**Uninstalling:**

To conveniently remove bindings from buttons, click the "Remove Bindings" button
in the settings pane.

**Contact:**

Feel free to submit feature requests or bugs on Github, or contact me on Discord at NitroP#7674.

**Please read this document fully before contacting me about bugs.  Thank you!**
