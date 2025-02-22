from datetime import datetime


class CacheEntry:
    def __init__(self, data, timestamp=None):
        self.data = data
        self.timestamp = timestamp or datetime.utcnow()

    def is_expired(self, max_age_seconds=600):
        """Check if cached entry is older than max_age_seconds."""
        return (datetime.utcnow() - self.timestamp).total_seconds() > max_age_seconds
