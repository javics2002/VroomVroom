 Entities = {
	Circuit = {
	    Transform = {
            position = { x = -65, y = 5, z = 0 },
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
	    },
	    RigidBody = {
		    colShape = 1,
		    mvType = static,
		    mass = 5,
            group = 2,
            mask = 6,
            colliderscale = {x = 200, y = 0.01, z = 200},
		    restitution = .5,
		    friction = .3,
		    isTrigger = false
	    },
        collider = {
            
        },
        meshrenderer = {
            mesh = "circuit",
            meshName = "Circuito.mesh",
        },
        CircuitInfo = {
            laps = 3
        },
        audiosource = {
            name = "bgRaceMusic",
            path = "musicaCircuito.mp3",
            onstart = true,
            loop = false,
            threed = false,
            groupchannel = "music",
            volume = 0.3
        }
	},

    laps0 = {
        UITransform = {
            position = { x = 0.35, y = 0.8 },
            scale = { x = 0.1, y = 0.177 },
            rotation = 0
        },
        UIText ={
            name = "laps0",
            text = "LAP 1/3",
            dimension = { x = 0.3 , y = 0.3},
            charheight = 0.1,
            position = { x = 0.85, y = 0.85 },
            fontname = "Mario"
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

    -------------------------------------------------------------
    ---------           primer jugador                  ---------
    -------------------------------------------------------------

	Car1 = {
        Transform = {
            position = { x=-50, y = 5.5, z = -10 },
            scale = { x = 0.7, y = 0.7, z = 0.7 },
            rotation = {x = 0, y = 0, z = 0}
        },
        RigidBody = {
            colShape = 2,
            mvType = 0,
            mass = 1,
            group = 2,
            mask = 7,
            colliderscale = {x = 1, y = .4, z = 1},
            restitution = 0,
            friction = 0,
            isTrigger = false
        },
        vehicleController = {
            acceleration = 0.2,
            rotationspeed = 0.12,
			maxspeed = 12,
			maxrotationspeed = 3,
            playerNumber = 0
        },
        collider = {
            
        },
        powerupuiwheel = {
            spinspeed = 0.1;
            linkedsprite = "insidecontainer"
        },
        meshrenderer = {
            mesh = "kartone",
            meshName = "RedCar.mesh",
        },
        audiolistener = {

        },
        audiosource = {
            name = "thunderCarOne",
            path = "posibleAumentoDeVel.mp3",
            onstart = false,
            loop = false,
            threed = true,
            groupchannel = "effects"
        }
	},

    FinishAudio1 ={
        transform={
            parentname = "car1";
        },
        audiosource={
            name = "finishCarOne",
            path = "endRace.mp3",
            onstart = false,
            loop = false,
            threed = false,
            groupchannel = "effects"
        }
    },

    camera1 = {
        transform = {
            position = { x= -55, y = 7.5, z = -10 }, --  x=-70, y = 100, z = 0
            rotation = { x=0, y = 0, z =0}
        },
        camera = {
            lookat = { x= -50, y = 6.5, z = -10 }, -- / x=-70, y = 0, z = 0
            name = "playerOne",
            neardistance = 0.5,
            fardistance = 100000,
            autoratio = true,
            zorder = 0,
            overlayenable = false,
            backgroundcolor = { r = .72, g = .92, b = 1, a = 1  },
            viewport = { left = 0.0, right = 0.0, width = 1.0, height =1.0 }
        },
		camerafollow = {
			target = "car1",
			positionoffset = { x= 0, y = 2, z = -5 },
            lookoffset = { x= 0, y = 1, z = 0 },
            smoothing = .2
		}
    },

    container = {
        UITransform = {
            position = { x = 0.04, y = 0.07 },
            scale = { x = 0.1, y = 0.178 },
            rotation = 0
        },
        UISpriteRenderer = {
            sprite = "container",     -- Nombre Interno
            materialName = "container",  -- Nombre en MaterialsResource
            zorder = 0
        }
    },

    insidecontainer = {
        UITransform = {
            position = { x = 0.066, y = 0.096 },
            scale = { x = 0.06, y = 0.1 },
            rotation = 0
        },
        UISpriteRenderer = {
            sprite = "insidecontainer",     -- Nombre Interno
            materialName = "insidecontainer",  -- Nombre en MaterialsResource
            zorder = 1
        }
    },

    place1 = {
        UITransform = {
            position = { x = 2, y = 2 },
            scale = { x = 0.1, y = 0.177 },
            rotation = 0
        },
        UISpriteRenderer ={
            sprite = "place1",     -- Nombre Interno
            materialName = "first"  -- Nombre en MaterialsResource
        }
    },


    finish0 = {
        UITransform = {
            position = { x = 450, y = 250 },
            scale = { x = 0.3, y = 0.4 },
            rotation = 0
        },
        UIText ={
            name = "finish0",
            text = "FINISH!",
            position = { x = 0.5, y = 0.35 },
            charheight = 0.4,
            fontname = "Mario"
        }
    },

    chrono0 = {
        UITransform = {
            position = { x = 10, y = 540 },
            scale = { x = 0.1, y = 0.177 },
            rotation = 0
        },
        UIText ={
            name = "chono",
            text = "00:00.000",
            position = { x = 0.85, y = 0.05 },
            charheight = 0.1,
            fontname = "Mario"
        }
    },

    ------------------------------------------------------------------------------------------
    ------------------------------------------------------------------------------------------

    countdownUI = {
        UITransform = {
            position = { x = 0.4, y = 0.33 },
            scale = { x = 0.2, y = 0.355 },
            rotation = 0
        },
        UISpriteRenderer ={
            sprite = "countdown",     -- Nombre Interno
            materialName = "countdown3"  -- Nombre en MaterialsResource
        },
        transform = {

        },
        audiosource = {
            name = "countDownSound",
            path = "comienzoCarrera.mp3",
            onstart = true,
            loop = false,
            threed = false,
            groupchannel = "music"
        }
    },

    DirectionalLight = {
        Transform = {
            position = { x = 0, y = 500, z = 500 }
        },
        Light = {
            name = "DirectionalLight",
            direction = { x = 1, y = -1, z = -1 },
            type = 0,
            color = { r = .5, g = .5, b = .5 },
            ambientColor = { r = .5, g = .5, b = .5 }
        }
    },

    -------------------------------------------------------------
    ---------           decoracion circuito              --------
    -------------------------------------------------------------

    Trees = {
	    Transform = {
            position = { x = -70, y = 4, z = -37},
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1} --80 30 40
	    },
        meshrenderer = {
            mesh = "arboles",
            meshName = "Arboles.mesh",
        }
	},
    Houses = {
	    Transform = {
            position = { x = -80, y = 4, z = -35},
			rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1} --80 30 40
	    },
        meshrenderer = {
            mesh = "houses",
            meshName = "Casas.mesh",
        }
	}
}


function createWalls()

    
    --Paredes interiores

    insideWallsTr = {

        Transform0 = {
            position = { x = -63, y = 5, z = 2.8},
            rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform1 = {
            position = { x = -63, y = 5, z = -2.8},
            rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform2 = {
            position = { x = -7.2, y = 5, z = 0},
            rotation = { x = 0, y = 90, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform3 = {
            position = { x = -7.4, y = 5, z = -0.8},
            rotation = { x = 0, y = -70, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform4 = {
            position = { x = -8.2, y = 5, z = -2},
            rotation = { x = 0, y = -50, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform5 = {
            position = { x = -7.4, y = 5, z = 0.8},
            rotation = { x = 0, y = 70, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform6 = {
            position = { x = -8.2, y = 5, z = 2},
            rotation = { x = 0, y = 50, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform7 = {
            position = { x = -119, y = 5, z = 0},
            rotation = { x = 0, y = 90, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform8 = {
            position = { x = -119, y = 5, z = 0.8},
            rotation = { x = 0, y = -70, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform9 = {
            position = { x = -118, y = 5, z = 2},
            rotation = { x = 0, y = -40, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform10 = {
            position = { x = -119, y = 5, z = -0.8},
            rotation = { x = 0, y = 70, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform11 = {
            position = { x = -118, y = 5, z = -2},
            rotation = { x = 0, y = 40, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        }
    }

    --Escalas de los colliders de las paredes interiores
    collidersScaleIW = {
        {x = 54, y = 10, z = 0.01},
        {x = 0.8, y = 10, z = 0.01}
    }

    local s = 1

    for i = 1, 12, 1 do
        if i >= 3 then s = 2 end
        wall = {
            Transform = insideWallsTr["Transform" .. i-1],
            RigidBody = {
                colShape = 1,
                mvType = static,
                mass = 5,
                group = 1,
                mask = 2,
                colliderscale = collidersScaleIW[s],
                restitution = .5,
                friction = .3,
                isTrigger = false
            },
            collider = {}
        }

       Entities["insideWall" .. i-1] = wall
    end

    --Paredes exteriores

    outsideWallsTr = {

        Transform0 = {
            position = { x = -50, y = 5, z = 13},
            rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform1 = {
            position = { x = -50, y = 5, z = -13},
            rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform2 = {
            position = { x = 2.5, y = 5, z = 0},
            rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform3 = {
            position = { x = 1, y = 5, z = -6},
            rotation = { x = 0, y = 27, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform4 = {
            position = { x = 0, y = 5, z = -8},
            rotation = { x = 0, y = 42, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform5 = {
            position = { x = -2, y = 5, z = -11},
            rotation = { x = 0, y = 65, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform6 = {
            position = { x = 1.5, y = 5, z = 6},
            rotation = { x = 0, y = -27, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform7 = {
            position = { x = 0, y = 5, z = 8},
            rotation = { x = 0, y = -42, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform8 = {
            position = { x = -2, y = 5, z = 11},
            rotation = { x = 0, y = -65, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform9 = {
            position = { x = -129, y = 5, z = 0},
            rotation = { x = 0, y = 0, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform10 = {
            position = { x = -127.2, y = 5.5, z = 6},
            rotation = { x = 0, y = 27, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform11 = {
            position = { x = -126.5, y = 5, z = 8},
            rotation = { x = 0, y = 42, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform12 = {
            position = { x = -124.5, y = 5, z = 11},
            rotation = { x = 0, y = 65, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform13 = {
            position = { x = -127.2, y = 5.5, z = -6},
            rotation = { x = 0, y = -27, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform14 = {
            position = { x = -126.5, y = 5, z = -8},
            rotation = { x = 0, y = -42, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },

        Transform15 = {
            position = {x = -124.5, y = 5, z = -11},
            rotation = { x = 0, y = -65, z = 0 },
            scale = { x = 1, y = 1, z = 1}
        },
    }

    --Escalas de los colliders de las paredes interiores
    collidersScaleOW = {
        {x = 100, y = 10, z = 0.01},
        {x = 0.01, y = 10, z = 10}
    }

    s = 1

    for i = 1, 16, 1 do
        if i >= 3 then s = 2 end
        wall = {
            Transform = outsideWallsTr["Transform" .. i-1],
            RigidBody = {
                colShape = 1,
                mvType = static,
                mass = 5,
                group = 1,
                mask = 2,
                colliderscale = collidersScaleOW[s],
                restitution = .5,
                friction = .3,
                isTrigger = false
            },
            collider = {}
        }

       Entities["outsideWall" .. i-1] = wall
    end

end


function createCheckpoints()


    checkpointPositions = {
        { x = -42, y = 0, z = -10 },
        { x = 0, y = 0, z = 0 },
        { x = -80, y = 0, z = 10 },
        { x = -120, y = 0, z = 0 }
    }

    checkpointRotation = {
        180, 90, 180, 90
    }

    for i = 1, 4, 1 do
        checkpoint = {
            Transform = {
                position = checkpointPositions[i],
                scale = { x = 1, y = 1, z = 1 },
                rotation = { x = 0, y = checkpointRotation[i], z = 0 }
            },
            RigidBody = {
                colShape = 1,
                mvType = static,
                mass = 5,
                group = 1,
                mask = 2,
                colliderscale = { x = 1, y = 10, z = 10 },
                restitution = 0.5,
                friction = 0.5,
                isTrigger = true
            },
            collider = {},
            Checkpoint = {
                index = i - 1;
            }
        }

       Entities["checkpoint" .. i-1] = checkpoint
    end

end


