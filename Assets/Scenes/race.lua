Entities = {
	Circuit = {
	    Transform = {
            position = { x = 0, y = 5, z = 0 },
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 80, y = 25, z = 25} --80 30 40
	    },
	    RigidBody = {
		    colShape = 2,
		    mvType = static,
		    mass = 5,
            group = 2,
            mask = 6,
            colliderscale = {x = 1.5, y = 0.01, z = 1.5},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {
            
        },
        meshrenderer = {
            mesh = "circuit",
            meshName = "Circuito.mesh",
            -- materialName = "Material/roja"
        }
	},

	Car = {
        Transform = {
            position = { x= 0, y = 6.5, z = -10 },
            scale = { x = 0.5, y = 0.5, z = 0.5 },
            rotation = {x = 0, y = 180, z = 0}
        },
        RigidBody = {
            colShape = 1,
            mvType = 0,
            mass = 1,
            group = 2,
            mask = 7,
            colliderscale = {x = 4, y = 2, z = 4},
            restitution = .5,
            friction = 0.5,
            isTrigger = false
        },
        VehicleController = {
            speed = 250;
            rotationfactor = 0.9;
            driftFactor = 1;
            playerNumber = 0;
        },
        Collider = {
            
        },
        MeshRenderer = {
            mesh = "kart",
            meshName = "Kart.mesh",
            --materialName = "Material/roja"
        }
	},

    TurningPoint = {
        Transform = {
            position = { x= 0, y = 6.5, z = -10 },
            scale = { x = 0.01, y = 0.01, z = 0.01 },
            rotation = {x = 0, y = 0, z = 0}
        },
        MeshRenderer = {
            mesh = "sphere",
            meshName = "sphere.mesh"
        }
    },

    Compass = {
        Transform = {
            position = { x= -30, y = 6.5, z = -10 },
            scale = { x = 3, y = 0.5, z = 0.5 },
            rotation = {x = 0, y = 0, z = 0 }
        },
        MeshRenderer = {
            mesh = "fish",
            meshName = "fish.mesh"
        }
    },

    PowerUp = {
        Transform = {
            position = { x= -25, y = 7.5, z = -10 },
            scale = { x = 1, y = 1, z = 1 },
            rotation = {x = 0, y = 90, z = 0 }
        },
        RigidBody = {
            colShape = 1,
            mvType = 0,
            mass = 0,
            group = 2,
            mask = 7,
            colliderscale = {x = 50, y = 50, z = 50},
            restitution = .5,
            friction = 0.5,
            isTrigger = true
        },
        meshrenderer = {
            mesh = "PowerUp",
            meshName = "PowerUp.mesh"
        },
        collider = {
            
        },
        PowerUpObject = {
            type = 2
        }
    },
    
    camera = {
        transform = {
            position = { x = -80, y = 30, z = 0 } -- -104 70 0 / 20 10 -10
        },
        camera = {
            lookat = { x = -80, y = 10, z = 0 }, -- -104 10 0 / -20 10 -10
            name = "main",
            neardistance = 0.5,
            fardistance = 100000,
            autoratio = true,
            zorder = 0,
            backgroundcolor = { r = .72, g = .92, b = 1, a = 1  }
        },
		camerafollow = {
			target = "car",
			offset = { x= 20, y = 10, z = -10 }
		}
    },

    DirectionalLight = {
        Transform = {
            position = { x = 0, y = 500, z = 500 }
        },
        Light = {
            name = "DirectionalLight",
            direction = { x = 1, y = -1, z = -1 },
            type = 0
        }
    }
}


