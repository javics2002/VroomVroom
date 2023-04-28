Entities = {
	Circuit = {
	    Transform = {
            position = { x = 0, y = 5, z = 0 },
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1.5, y = 3, z = 4} --80 30 40
	    },
	    RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 2,
            mask = 6,
            colliderscale = {x = 70, y = 0.01, z = 20},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {
            
        },
        meshrenderer = {
            mesh = "circuit",
            meshName = "Circuit.mesh",
            -- materialName = "Material/roja"
        },
        CircuitInfo = {
            laps = 3
        }
	},
    
    camera = {
        transform = {
            position = { x = 0, y = 200, z = 0 } -- -104 70 0 / 20 10 -10
        },
        camera = {
            lookat = { x = 0, y = 1, z = 0 }, -- -104 10 0 / -20 10 -10
            name = "main",
            neardistance = 0.5,
            fardistance = 1,
            autoratio = true,
            zorder = 3,
            overlayenable = true,
            backgroundcolor = { r = .72, g = .92, b = 1, a = 1  },
            viewport = { left = 0.0, right = 0.0, width = 1.0, height =1.0 }
        }
    },


	CarOne = {
        Transform = {
            position = { x= 0, y = 10, z = -5 },
            scale = { x = 1, y = 1, z = 1 },
            rotation = {x = 0, y = 180, z = 0}
        },
        RigidBody = {
            colShape = 1,
            mvType = 0,
            mass = 1,
            group = 2,
            mask = 7,
            colliderscale = {x = 1, y = 1, z = 1},
            restitution = .5,
            friction = 0.5,
            isTrigger = false
        },
        vehicleController = {
            speed = 1000,
            rotationspeed = 200,
            driftFactor = 1,
            playerNumber = 0
        },
        collider = {
            
        },
        powerupuiwheel = {
            spinspeed = 0.1;
            linkedsprite = "insideroundedsquare"
        },
        meshrenderer = {
            mesh = "kartone",
            meshName = "Car.mesh",
            --materialName = "Material/roja"
        }
	},

    cameraOne = {
        transform = {
            position = { x = -90, y = 100, z = 0 } -- -104 70 0 / 20 10 -10
        },
        camera = {
            lookat = { x = -9, y = 1, z = 0 }, -- -104 10 0 / -20 10 -10
            name = "playerOne",
            neardistance = 0.5,
            fardistance = 100000,
            autoratio = true,
            zorder = 0,
            overlayenable = false,
            backgroundcolor = { r = .72, g = .92, b = 1, a = 1  },
            viewport = { left = 0.0, right = 0.0, width = 0.5, height =1.0 }
        },
		camerafollow = {
			target = "carone",
			offset = { x= 20, y = 10, z = -10 }
		}
    },


    CarTwo = {
        Transform = {
            position = { x= 0, y = 10, z = -10 },
            scale = { x = 1, y = 1, z = 1 },
            rotation = {x = 0, y = 180, z = 0}
        },
        RigidBody = {
            colShape = 1,
            mvType = 0,
            mass = 1,
            group = 2,
            mask = 7,
            colliderscale = {x = 1, y = 1, z = 1},
            restitution = .5,
            friction = 0.5,
            isTrigger = false
        },
        vehicleController = {
            speed = 1000,
            rotationspeed = 200,
            driftFactor = 1,
            playerNumber = 1
        },
        collider = {
            
        },
        powerupuiwheel = {
            spinspeed = 0.1;
            linkedsprite = "insideroundedsquare"
        },
        meshrenderer = {
            mesh = "karttwo",
            meshName = "Car.mesh",
            --materialName = "Material/roja"
        }
	},
    
    cameraTwo = {
        transform = {
            position = { x = -90, y = 100, z = 0 } -- -104 70 0 / 20 10 -10
        },
        camera = {
            lookat = { x = -9, y = 1, z = 0 }, -- -104 10 0 / -20 10 -10
            name = "playerTwo",
            neardistance = 0.5,
            fardistance = 100000,
            autoratio = true,
            zorder = 1,
            overlayenable = false,
            backgroundcolor = { r = .72, g = .92, b = 1, a = 1  },
            viewport = { left = 0.5, top = 0.0, width = 0.5, height =1.0 }
        },
		camerafollow = {
			target = "cartwo",
			offset = { x= 20, y = 10, z = -10 }
		}
    },

    insideRoundedSquare = {
        UITransform = {
            position = { x = 0.04, y = 0.07 },
            scale = { x = 0.06, y = 0.1 },
            rotation = 0
        },
        UISpriteRenderer = {
            sprite = "iRoundedSquare",     -- Nombre Interno
            materialName = "insideRoundedSquare"  -- Nombre en MaterialsResource
        }
    },

    countdownUI = {
        UITransform = {
            position = { x = 0.4, y = 0.4 },
            scale = { x = 0.2, y = 0.2 },
            rotation = 0
        },
        UISpriteRenderer ={
            sprite = "countdown",     -- Nombre Interno
            materialName = "countdown3"  -- Nombre en MaterialsResource
        }
    },
    
    -- PowerUp1 = {
    --     Transform = {
    --         position = { x= 90, y = 7.5, z = 0 },
    --         scale = { x = 0.015, y = 0.015, z = 0.015 },
    --         rotation = {x = 0, y = 180, z = 0}
    --     },
    --     RigidBody = {
    --         colShape = 1,
    --         mvType = 0,
    --         mass = 0,
    --         group = 2,
    --         mask = 7,
    --         colliderscale = {x = 40, y = 40, z = 40},
    --         restitution = .5,
    --         friction = 0.5,
    --         isTrigger = true
    --     },
    --     meshrenderer = {
    --         mesh = "powerUp1",
    --         meshName = "cube.mesh"
    --     },
    --     collider = {
            
    --     },
    --     PowerUpObject = {
    --         type = 2
    --     }
    -- },

    -- PowerUp2 = {
    --     Transform = {
    --         position = { x= 95, y = 7.5, z = 0 },
    --         scale = { x = 0.015, y = 0.015, z = 0.015 },
    --         rotation = {x = 0, y = 180, z = 0}
    --     },
    --     RigidBody = {
    --         colShape = 1,
    --         mvType = 0,
    --         mass = 0,
    --         group = 2,
    --         mask = 7,
    --         colliderscale = {x = 40, y = 40, z = 40},
    --         restitution = .5,
    --         friction = 0.5,
    --         isTrigger = true
    --     },
    --     meshrenderer = {
    --         mesh = "powerUp2",
    --         meshName = "cube.mesh"
    --     },
    --     collider = {
            
    --     },
    --     PowerUpObject = {
    --         type = 2
    --     }
    -- },

    -- PowerUp3 = {
    --     Transform = {
    --         position = { x= 100, y = 7.5, z = 0 },
    --         scale = { x = 0.015, y = 0.015, z = 0.015 },
    --         rotation = {x = 0, y = 180, z = 0}
    --     },
    --     RigidBody = {
    --         colShape = 1,
    --         mvType = 0,
    --         mass = 0,
    --         group = 2,
    --         mask = 7,
    --         colliderscale = {x = 40, y = 40, z = 40},
    --         restitution = .5,
    --         friction = 0.5,
    --         isTrigger = true
    --     },
    --     meshrenderer = {
    --         mesh = "powerUp3",
    --         meshName = "cube.mesh"
    --     },
    --     collider = {
            
    --     },
    --     PowerUpObject = {
    --         type = 2
    --     }
    -- },

    -- PowerUp4 = {
    --     Transform = {
    --         position = { x= -85, y = 7.5, z = 0 },
    --         scale = { x = 0.015, y = 0.015, z = 0.015 },
    --         rotation = {x = 0, y = 180, z = 0}
    --     },
    --     RigidBody = {
    --         colShape = 1,
    --         mvType = 2,
    --         mass = 1,
    --         group = 2,
    --         mask = 7,
    --         colliderscale = {x = 40, y = 40, z = 40},
    --         restitution = .5,
    --         friction = 0.5,
    --         isTrigger = true
    --     },
    --     meshrenderer = {
    --         mesh = "powerUp4",
    --         meshName = "cube.mesh"
    --     },
    --     collider = {
            
    --     },
    --     PowerUpObject = {
    --         type = 2
    --     }
    -- },

    -- PowerUp5 = {
    --     Transform = {
    --         position = { x= -90, y = 7.5, z = 0 },
    --         scale = { x = 0.015, y = 0.015, z = 0.015 },
    --         rotation = {x = 0, y = 180, z = 0}
    --     },
    --     RigidBody = {
    --         colShape = 1,
    --         mvType = 2,
    --         mass = 1,
    --         group = 2,
    --         mask = 7,
    --         colliderscale = {x = 40, y = 40, z = 40},
    --         restitution = .5,
    --         friction = 0.5,
    --         isTrigger = true
    --     },
    --     meshrenderer = {
    --         mesh = "powerUp5",
    --         meshName = "cube.mesh"
    --     },
    --     collider = {
            
    --     },
    --     PowerUpObject = {
    --         type = 2
    --     }
    -- },

    -- PowerUp6 = {
    --     Transform = {
    --         position = { x= -95, y = 7.5, z = 0 },
    --         scale = { x = 0.015, y = 0.015, z = 0.015 },
    --         rotation = {x = 0, y = 180, z = 0}
    --     },
    --     RigidBody = {
    --         colShape = 1,
    --         mvType = 2,
    --         mass = 1,
    --         group = 2,
    --         mask = 7,
    --         colliderscale = {x = 40, y = 40, z = 40},
    --         restitution = .5,
    --         friction = 0.5,
    --         isTrigger = true
    --     },
    --     meshrenderer = {
    --         mesh = "powerUp6",
    --         meshName = "cube.mesh"
    --     },
    --     collider = {
            
    --     },
    --     PowerUpObject = {
    --         type = 2
    --     }
    -- },
    -- -- checkpoint0 = {
    -- --     Transform = {
    -- --         position = { x= 30, y = 10, z = -10 },
    -- --         scale = { x = 1, y = 1, z = 1 },
    -- --         rotation = {x = 0, y = 180, z = 0}
    -- --     },
    -- --     RigidBody = {
    -- --         colShape = 1,
    -- --         mvType = static,
    -- --         mass = 5,
    -- --         group = 1,
    -- --         mask = 2,
    -- --         colliderscale = {x = 0.01, y = 10, z = 10},
    -- --         restitution = .5,
    -- --         friction = 0.5,
    -- --         isTrigger = true
    -- --     },
    -- --     collider = {

    -- --     },
    -- --     Checkpoint={
    -- --         index = 0;
    -- --     }
    -- -- },
    


    -- -- checkpoint = {
    -- --     Transform = {
    -- --         position = { x= 10, y = 10, z = -10 },
    -- --         scale = { x = 0.5, y = 0.5, z = 0.5 },
    -- --         rotation = {x = 0, y = 180, z = 0}
    -- --     },
    -- --     -- RigidBody = {
    -- --     --     colShape = 1,
    -- --     --     mvType = 1,
    -- --     --     mass = 1,
    -- --     --     group = 2,
    -- --     --     mask = 7,
    -- --     --     colliderscale = {x = 4, y = 2, z = 4},
    -- --     --     restitution = .5,
    -- --     --     friction = 0.5,
    -- --     --     isTrigger = false
    -- --     -- },
    -- --     meshrenderer = {
    -- --         mesh = "check",
    -- --         meshName = "cube.mesh",
    -- --         --materialName = "Material/roja"
    -- --     },
    -- --     checkpoint = {
    -- --         index = 0
    -- --     }
    -- -- },

    -- -- DirectionalLight2 = {
    -- --     Transform = {
    -- --         position = { x = 0, y = 500, z = 500 }
    -- --     },
    -- --     Light = {
    -- --         name = "DirectionalLight2",
    -- --         direction = { x = -1, y = -1, z = -1 },
    -- --         type = 0
    -- --     }
    -- -- }, 

    DirectionalLight = {
        Transform = {
            position = { x = 0, y = 500, z = 500 }
        },
        Light = {
            name = "DirectionalLight",
            direction = { x = 1, y = -1, z = -1 },
            type = 0
        }
    },

    -- -- Paredes del centro del circuito

    -- ParedCentroDerecha = {
    --     Transform = {
    --         position = { x = 2.5, y = 5, z = 4.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 82.5, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentroIzquierda = {
    --     Transform = {
    --         position = { x = 2.5, y = 5, z = -4.5},
	-- 		rotation = { x = 0, y = 0, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 82.5, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro1 = {
    --     Transform = {
    --         position = { x = 88.5, y = 5, z = 0},
	-- 		rotation = { x = 0, y = 90, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro2 = {
    --     Transform = {
    --         position = { x = 88.3, y = 5, z = -1.5},
	-- 		rotation = { x = 0, y = -70, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro3 = {
    --     Transform = {
    --         position = { x = 87.5, y = 5, z = -2.5},
	-- 		rotation = { x = 0, y = -50, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro4 = {
    --     Transform = {
    --         position = { x = 86.5, y = 5, z = -3.5},
	-- 		rotation = { x = 0, y = -40, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro5 = {
    --     Transform = {
    --         position = { x = 85.5, y = 5, z = -4},
	-- 		rotation = { x = 0, y = -30, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro6 = {
    --     Transform = {
    --         position = { x = 88.3, y = 5, z = 1.5},
	-- 		rotation = { x = 0, y = 70, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro7 = {
    --     Transform = {
    --         position = { x = 87.5, y = 5, z = 2.5},
	-- 		rotation = { x = 0, y = 50, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro8 = {
    --     Transform = {
    --         position = { x = 86.5, y = 5, z = 3.5},
	-- 		rotation = { x = 0, y = 40, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro9 = {
    --     Transform = {
    --         position = { x = 85.5, y = 5, z = 4},
	-- 		rotation = { x = 0, y = 30, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro10 = {
    --     Transform = {
    --         position = { x = -83.5, y = 5, z = 0},
	-- 		rotation = { x = 0, y = 90, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro11 = {
    --     Transform = {
    --         position = { x = -83.3, y = 5, z = 1.5},
	-- 		rotation = { x = 0, y = -70, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro12 = {
    --     Transform = {
    --         position = { x = -82.5, y = 5, z = 2.5},
	-- 		rotation = { x = 0, y = -50, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro13 = {
    --     Transform = {
    --         position = { x = -81.5, y = 5, z = 3.5},
	-- 		rotation = { x = 0, y = -40, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro14 = {
    --     Transform = {
    --         position = { x = -80.5, y = 5, z = 4},
	-- 		rotation = { x = 0, y = -30, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro15 = {
    --     Transform = {
    --         position = { x = -83.3, y = 5, z = -1.5},
	-- 		rotation = { x = 0, y = 70, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro16 = {
    --     Transform = {
    --         position = { x = -82.5, y = 5, z = -2.5},
	-- 		rotation = { x = 0, y = 50, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro17 = {
    --     Transform = {
    --         position = { x = -81.5, y = 5, z = -3.5},
	-- 		rotation = { x = 0, y = 40, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- ParedCentro18 = {
    --     Transform = {
    --         position = { x = -80.5, y = 5, z = -4},
	-- 		rotation = { x = 0, y = 30, z = 0 },
    --         scale = { x = 1, y = 1, z = 1}
	--     },
    --     RigidBody = {
	-- 	    colShape = 1,
	-- 	    mvType = static,
	-- 	    mass = 5,
    --         group = 1,
    --         mask = 2,
    --         colliderscale = {x = 0.8, y = 10, z = 0.01},
	-- 	    restitution = .5,
	-- 	    friction = .3,
	-- 	    isTrigger = false
	--     },
    --     collider = {}
    -- },

    -- --Paredes del exterior del circuito

    ParedDerecha = {
        Transform = {
            position = { x = 0, y = 5, z = 20.5},
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 91, y = 10, z = 0.01},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedIzquierda = {
        Transform = {
            position = { x = 0, y = 5, z = -20.5},
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 91, y = 10, z = 0.01},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFondo1 = {
        Transform = {
            position = { x = 104, y = 5, z = 0},
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFondo2 = {
        Transform = {
            position = { x = 101, y = 5, z = -12},
			rotation = { x = 0, y = 22, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 20},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFondo3 = {
        Transform = {
            position = { x = 100, y = 5, z = -12},
			rotation = { x = 0, y = 35, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFondo4 = {
        Transform = {
            position = { x = 97, y = 5, z = -15},
			rotation = { x = 0, y = 50, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFondo5 = {
        Transform = {
            position = { x = 101, y = 5, z = 12},
			rotation = { x = 0, y = -22, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 20},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFondo6 = {
        Transform = {
            position = { x = 100, y = 5, z = 12},
			rotation = { x = 0, y = -35, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFondo7 = {
        Transform = {
            position = { x = 97, y = 5, z = 15},
			rotation = { x = 0, y = -50, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFrente1 = {
        Transform = {
            position = { x = -98.5, y = 5, z = 0},
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFrente2 = {
        Transform = {
            position = { x = -95.5, y = 5.5, z = -12},
			rotation = { x = 0, y = -22, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 20},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFrente3 = {
        Transform = {
            position = { x = -94.5, y = 5, z = -12},
			rotation = { x = 0, y = -35, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFrente4 = {
        Transform = {
            position = { x = -91.5, y = 5, z = -15},
			rotation = { x = 0, y = -50, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFrente5 = {
        Transform = {
            position = { x = -95.5, y = 5.5, z = 12},
			rotation = { x = 0, y = 22, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 20},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFrente6 = {
        Transform = {
            position = { x = -94.5, y = 5, z = 12},
			rotation = { x = 0, y = 35, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    },

    ParedFrente7 = {
        Transform = {
            position = { x = -91.5, y = 5, z = 15},
			rotation = { x = 0, y = 50, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
        RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 1,
            mask = 2,
            colliderscale = {x = 0.01, y = 10, z = 10},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {}
    }


        -- SpriteTest2 = {
    --     UITransform = {
    --         position = { x = 0.8, y = 0.8 },
    --         scale = { x = 0.1, y = 0.15 },
    --         rotation = 0
    --     },
    --     UISpriteRenderer = {
    --         sprite = "lightning",     -- Nombre Interno
    --         materialName = "lightningBolt"  -- Nombre en MaterialsResource
    --     }
    -- },

    -- SpriteTest3 = {
    --     UITransform = {
    --         position = { x = 0.05, y = 0.8 },
    --         scale = { x = 0.1, y = 0.15 },
    --         rotation = 0
    --     },
    --     UISpriteRenderer = {
    --         sprite = "nerf",     -- Nombre Interno
    --         materialName = "nerf"  -- Nombre en MaterialsResource
    --     }
    -- },
}


