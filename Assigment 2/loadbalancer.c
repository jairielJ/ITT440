var slb = require("socket-load-balancer");

var router = slb.routers.RoundRobin({
	routes: [
	{port: 3001},
	{port: 3002}
	]
});

var server = slb.Server({
	router: router
})
server.listen(3000);

