# Overlights

Reactive lighting effects for hue + overwatch :bulb: :shield:

![Build Status](https://b3ngr33ni3r.visualstudio.com/_apis/public/build/definitions/e281a50c-d98a-4097-8a58-587654e97c7f/1/badge)

Overlights is both a library for consuming lighting data from overwatch, as well as an application to allow you to read said lighting data and map the data points to hue lights.

This allows you to have a reactive lighting setup that changes in realtime in response to game events!

![example](./readme_data/example.gif)

## How to set things up (quick)

> You can read a more detailed walkthrough [here](./readme_data/detailed-setup.md).

+ Download [the latest build](https://github.com/bengreenier/overlights/releases/latest) and extract the `.zip`
+ Copy `*.dll` from `Build/` to the directory `Overwatch.exe` is in
+ Run `Overlights.exe` from `Build/`
+ Run `Overwatch.exe`
+ See lighting data being emitted from the game on virtual "keys"
+ Navigate to `Setup -> Hue` to configure hue lights
+ Map configured hue lights to keys by clicking on the virtual "key" 

## License

MIT
