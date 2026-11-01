import unittest
from src import Source_Files, Constellation

class TestParsing(unittest.TestCase):
    def test_constellation_parsing(self):
        print()
        for name, path in Source_Files["easy"].items():
            with self.subTest(name=name):
                constellation = Constellation(path)
                self.assertEqual(constellation._name, name)
                self.assertIsNotNone(constellation._start_hub)
                self.assertIsNotNone(constellation._end_hub)
                self.assertGreater(len(constellation._hubs), 0)
                self.assertGreater(len(constellation._connnections), 0)
                self.assertGreater(constellation._nb_drones, 0)
                constellation.simulate_drones()
                print("the routes:")
                constellation.print_simulation_routes()
