Entities = {
    
    gameManager = {
        GameManager = {}
    },


    camera = {
        transform = {
            position = { x = 0, y = 0, z = 0 }
        },
        camera = {
            lookat = { x = 1, y = 0, z = 0 },
            name = "main",
            neardistance = 1,
            fardistance = 10000,
            autoratio = true,
            zorder = 0,
            backgroundcolor = { r = .77, g = .54, b = .96, a = 1 }
        }
    },

    DirectionalLight = {
        Transform = {
            position = { x = 0, y = 500, z = 500 }
        },
        Light = {
            name = "mainlight",
            direction = { x = 1, y = -1, z = -1 },
            type = 0,
            color = { r = .5, g = .5, b = .5 },
            ambientColor = { r = .5, g = .5, b = .5 }
        }
    },
 

    Title = {
        UISpriteRenderer = {
            sprite = "maintitle",
            materialName = "Main/title",
            zorder = 2
        },
        UITransform = {
            position = { x = 0.39, y = .01 },
            scale = { x = 0.2, y = .35},
            rotation = 0
        }
    },


    bandera1 = {

        UISpriteRenderer = {
            sprite = "bandera1",
            materialName = "Main/bandera1",
            zorder = 1
        },
        UITransform = {
            position = { x = 0.59, y = 0.05 },
            scale = { x = 0.175, y = 0.31 },
            rotation = 1
        }
    },
    bandera2 = {

        UISpriteRenderer = {
            sprite = "bandera2",
            materialName = "Main/bandera2",
            zorder = 1
        },
        UITransform = {
            position = { x = 0.23, y = 0.05 },
            scale = { x = 0.175, y = 0.31 },
            rotation = 0
        }
    },


    Motor = {

        UISpriteRenderer = {
            sprite = "mainmotor",
            materialName = "Main/motor",
            zorder = 1
        },
        UITransform = {
            position = { x = 0.85, y = 0.05 },
            scale = { x = 0.1, y = 0.178 },
            rotation = 0
        }
    },

    background = {

        -- UISpriteRenderer = {
        --     sprite = "background",
        --     materialName = "Main/background",
        --     zorder = 0
        -- },
        -- UITransform = {
        --     position = { x = 0, y = 0 },
        --     scale = { x = 1, y = 1},
        --     rotation = 0
        -- }

        Transform = {
            position = { x = 200, y = 0, z = 0 },
            scale = { x = 1.8, y = 1, z = 1.8 },
            rotation = {x = 0, y = 0, z = 0}
        },
        meshrenderer = {
            mesh = "cube",
            meshName = "cube.mesh",
            materialName = "Main/background"
        }
    },


    QuitButton = {
	
        UIButtonScene = {
            sprite = "mainquitbutton",
            materialName = "Main/ResultsButton",
            scene = "mainmenu.lua",
            zorder = 3
        },

        UITransform = {
            position = { x = 0.66, y = 0.8 },
            scale = { x = 0.3, y = 0.135 },
            rotation = 0
        }
    },

    CarOne = {
        Transform = {
            position = { x = 6, y = -1, z = -2.5 },
            scale = { x = 0.8, y = 0.8, z = 0.8 },
            rotation = {x = -2, y = 200, z = 0}
        },
        meshrenderer = {
            mesh = "kartone",
            meshName = "RedCar.mesh",
        }
	},
    YourTime = {
        UITransform = {
            position = { x = 140, y = 220 },
            scale = { x = 0.3, y = 0.3 },
            rotation = 0
        },
        UIText ={
            name = "yourtime",
            text = "PLAYER ONE",
            colour = { x = 1, y = 0 , z = 0},
            charheight = 35,
            fontname = "Mario"
        }
    },
    YourTime1 = {
        UITransform = {
            position = { x = 365, y = 220 },
            scale = { x = 0.3, y = 0.3 },
            rotation = 0
        },
        UIText ={
            name = "yourtime1",
            text = "PLAYER TWO",
            colour = { x = 0, y = 0 , z = 1},
            charheight = 35,
            fontname = "Mario"
        }
    },
    CarTwo = {
        Transform = {
            position = { x = 6.2, y = -1.16, z = -0.5 },
            scale = { x = 0.8, y = 0.8, z = 0.8 },
            rotation = {x = 0, y = 178, z = 0}
        },
        meshrenderer = {
            mesh = "karttwo",
            meshName = "BlueCar.mesh",
        }
	},

    CarOneText = {
        UITransform = {
            position = { x = 150, y = 260 },
            scale = { x = 0.3, y = 0.3 },
            rotation = 0
        },
        UIText ={
            name = "caronetext",
            text = "00:00:00",
            colour = { x = 1, y = 0 , z = 0},
            charheight = 35,
            fontname = "Mario"
        }
    },
    CarTwoText = {
        UITransform = {
            position = { x = 400, y = 260 },
            scale = { x = 0.3, y = 0.3 },
            rotation = 0
        },
        UIText ={
            name = "cartwotext",
            text = "00:00:00",
            colour = { x = 0, y = 0 , z = 1},
            charheight = 35,
            fontname = "Mario"
        }
    },
    

}


