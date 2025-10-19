
class TimeSeriesInput(object):
    def __init__(self):
        self.datastreams:list = []
        self.namedstreams:dict = {}
        
        ''' This variable is an expected duration from first positive edge to the end of a full breathing wave '''
        self.first_positive_to_end_duration = 0

    

    def recordFullWave(self, data):
        pass
