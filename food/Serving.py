
class Serving:
    unit_types = ['G', 'OZ', 'LBS']
    """ The unit types we can handle """

    def __init__(self, unit, size, second_size=0):
        """
        The serving for the food being input to the database.

        @param unit:  The unit type of the serving (e.g. g, oz)
        @type  unit:  text

        @param size:  The quantity of the serving
        @type  size:  real

        @param second_size: The secondary quantity of the serving (e.g. lbs oz)
        @type: real

        """

        if unit.upper() not in Serving.unit_types:
            raise TypeError("""First argument must be a string of unit
                             in this list""" + str(Serving.unit_types))

        try:
            # Make sure they're numbers
            size + second_size + 1
        except TypeError:
            raise TypeError("Values must be numbers")

        self.size = size
        self.unit = unit
        self.second_size = second_size
