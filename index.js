const config = require('proxy-config')(process.argv[2] || '.lights.conf')
const huejay = require('huejay')
const aks = require('asynckeystate')

if (!config.color) {
    return console.error("please set config values for color")
}

huejay.discover()
    .then((bridges) => {
        return bridges[0]
    })
    .then((bridge) => {

        if (!config.username) {

            const client = new huejay.Client({
                host: bridge.ip
            })

            let user = new client.users.User()
            user.deviceType = 'overlights'

            console.log("press bridge button (waiting 10s)...")

            return new Promise((resolve, reject) => {
                setTimeout(() => {
                    resolve()
                }, 10*1000)
            })
                .then(() => client.users.create(user))
                .then((user) => {
                    config.username = user.username

                    return new huejay.Client({
                        host: bridge.ip,
                        username: config.username
                    })
                })
        } else {
            return new huejay.Client({
                host: bridge.ip,
                username: config.username
            })
        }
    })
    .then((client) => {

        console.log("capturing default light state...")

        return client.lights.getAll()
            .then((lights) => {

                console.log("default light state captured")

                return [client, lights]
            })
    })
    .then((arr) => {
        const client = arr[0]
        const lights = arr[1]

        console.log("running...")

        setInterval(() => {

            // TODO: abstract into config - this is currently q
            if (aks.getAsyncKeyState(0x51)) {
                
                console.log(`${new Date().toISOString()}: triggered`)

                Object.values(lights).forEach((light) => {
                    const state = {}

                    for (let prop in config.color) {
                        state[prop] = light[prop]
                        light[prop] = config.color[prop]
                    }

                    console.log(`changing ${light.name}`)

                    client.lights.save(light)
                        .then(() => {
                            for (let prop in state) {
                                light[prop] = state[prop]
                            }

                            light.transitionTime = 2

                            return client.lights.save(light)
                        }, (err) => {
                            console.error(`single light (${light.name}) error: ${err}`)
                        })
                })
            }
        }, 100)
    })
    .catch((err) => {
        console.error(`ERROR ${err.stack}`)
    })