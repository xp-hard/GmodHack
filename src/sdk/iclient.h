class IServer;
class INetMessage;

class IClient
{
public:
	virtual	~IClient() {}
	virtual int				GetPlayerSlot() const = 0; // returns client slot (usually entity number-1)
	virtual int				GetUserID() const = 0; // unique ID on this server 
	virtual const void	GetNetworkID() const = 0; // network wide ID
	virtual const char		*GetClientName() const = 0;	// returns client name
	virtual void		*GetNetChannel() = 0; // returns client netchannel
	virtual IServer			*GetServer() = 0; // returns the object server the client belongs to
	virtual const char		*GetUserSetting(const char *cvar) const = 0; // returns a clients FCVAR_USERINFO setting
	virtual const char		*GetNetworkIDString() const = 0; // returns a human readable representation of the network id

	// set/get client data rate in bytes/second
	virtual void	SetRate( int nRate, bool bForce ) = 0;
	virtual int		GetRate( void ) const = 0;
	
	// set/get updates/second rate
	virtual void	SetUpdateRate( int nUpdateRate, bool bForce ) = 0;
	virtual int		GetUpdateRate( void ) const = 0;	

	// clear complete object & free all memory 
	virtual void	Clear( void ) = 0;

	// returns the highest world tick number acknowledge by client
	virtual int		GetMaxAckTickCount() const = 0;
	
	// execute a client command
	virtual bool	ExecuteStringCommand( const char *s ) = 0;
	// send client a network message
	virtual bool	SendNetMsg(INetMessage &msg, bool bForceReliable = false) = 0;
	// send client a text message
	virtual void	ClientPrintf (const char *fmt, ...) = 0;

		// client has established network channels, nothing else
	virtual bool	IsConnected( void ) const = 0;
	// client is downloading signon data
	virtual bool	IsSpawned( void ) const = 0;
	// client active is ingame, receiving snapshots
	virtual bool	IsActive( void ) const = 0;
	// returns true, if client is not a real player
	virtual bool	IsFakeClient( void ) const = 0;
	// returns true, if client is a HLTV proxy
	virtual bool	IsHLTV( void ) const = 0;
#if defined( REPLAY_ENABLED )
	// returns true, if client is a Replay proxy
	virtual bool	IsReplay( void ) const = 0;
#else
	// !KLUDGE! Reduce number of #ifdefs required
	inline bool		IsReplay( void ) const { return false; }
#endif
	// returns true, if client hears this player
	virtual bool	IsHearingClient(int index) const = 0;
	// returns true, if client hears this player by proximity
	virtual bool	IsProximityHearingClient(int index) const = 0;

	virtual void	SetMaxRoutablePayloadSize( int nMaxRoutablePayloadSize ) = 0;
};
