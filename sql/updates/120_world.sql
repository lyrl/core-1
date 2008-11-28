-- Add/Edit/Move lang strings
DELETE FROM `trinity_string` WHERE `entry` IN (25,52,54,55,56,171,401,413,438,593,594,595,596,597,598,599,614,615,636,637,638,809,1000,1001,1002,1003,1004,1005,1006,1007,1008,1009,1010,1011,1100,1101,1102,1103,1104,1105,1106,1107,1108,1109,1110,1111,1112,1113,1114,1115,1116,1117,1118);
DELETE FROM `trinity_string` WHERE `entry` BETWEEN '667' AND '687';
DELETE FROM `trinity_string` WHERE `entry` BETWEEN '711' AND '716';
DELETE FROM `trinity_string` WHERE `entry` BETWEEN '730' AND '747';
DELETE FROM `trinity_string` WHERE `entry` BETWEEN '5000' AND '5006';
INSERT INTO trinity_string VALUES
('25','Password not changed (unknown error)!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
('52', 'Invaid item count (%u) for item %u', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('54','The new passwords do not match',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
('55','Your password can\'t be longer than 16 characters (client limit), password not changed!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
('56','Current Message of the day: \r\n%s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(171,'You are being teleported by server console command.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(401,'You change security level of account %s to %i.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(413,'Account not exist: %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(438,'Found items %u: %u ( inventory %u mail %u auction %u guild %u)',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(593,'Currently Banned Accounts:',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(594,'|    Account    |   BanDate    |   UnbanDate  |  Banned By    |   Ban Reason  |',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(595,'Currently Banned IPs:',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(596,'|      IP       |   BanDate    |   UnbanDate  |  Banned By    |   Ban Reason  |',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(597,'Current gamemasters:',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(598,'|    Account    |  GM  |',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(599,'No gamemasters.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
('614', 'The Alliance flag has been respawned!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('615', 'The Horde flag has been respawned!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('636', 'The Battle for Eye of the Storm begins in 1 minute.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('637', 'The Battle for Eye of the Storm begins in 30 seconds.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('638', 'The Battle for Eye of the Storm has begun!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('667', 'The Alliance has taken control of the Mage Tower!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('668', 'The Horde has taken control of the Mage Tower!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('669', 'The Alliance has taken control of the Draenei Ruins!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('670', 'The Horde has taken control of the Draenei Ruins!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('671', 'The Alliance has taken control of the Blood Elf Tower!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('672', 'The Horde has taken control of the Blood Elf Tower!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('673', 'The Alliance has taken control of the Fel Reaver Ruins!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('674', 'The Horde has taken control of the Fel Reaver Ruins!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('675', 'The Alliance has lost control of the Mage Tower!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('676', 'The Horde has lost control of the Mage Tower!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('677', 'The Alliance has lost control of the Draenei Ruins!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('678', 'The Horde has lost control of the Draenei Ruins!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('679', 'The Alliance has lost control of the Blood Elf Tower!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('680', 'The Horde has lost control of the Blood Elf Tower!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('681', 'The Alliance has lost control of the Fel Reaver Ruins!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('682', 'The Horde has lost control of the Fel Reaver Ruins!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('683', '$N has taken the flag!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('684', 'The Alliance has captured the flag!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('685', 'The Horde has captured the flag!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('686', 'The Flag has been dropped!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('687', 'The flag has been reset', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('711', 'Your group is too large for this battleground. Please regroup to join.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('712', 'Your group is too large for this arena. Please regroup to join.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('713', 'You must be level %u to join an arena team!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('714', '%s is not high enough level to join your team', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('715', 'You don\'t meet Battleground level requirements', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('716', 'Your arena team is full, %s cannot join it.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('730', 'Your group has members not in your arena team. Please regroup to join.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('731', 'Your group does not have enough players to join this match.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('732', 'The Gold Team wins!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('733', 'The Green Team wins!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('734', 'There aren\'t enough players in this battleground. It will end soon unless some more players join to balance the fight.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('735', 'Your group has an offline member. Please remove him before joining.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('736', 'Your group has players from the opposing faction. You can\'t join the battleground as a group.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('737', 'Your group has players from different battleground brakets. You can\'t join as group.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('738', 'Someone in your party is already in this battleground queue. (S)he must leave it before joining as group.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('739', 'Someone in your party is Deserter. You can\'t join as group.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('740', 'Someone in your party is already in three battleground queues. You cannot join as group.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('741', 'You cannot teleport to a battleground or arena map.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('742', 'You cannot summon players to a battleground or arena map.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('743', 'You must be in GM mode to teleport to a player in a battleground.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('744', 'You cannot teleport to a battleground from another battleground. Please leave the current battleground first.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('745', 'Arena testing turned %s', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('746','|cffff0000[Automatic]:|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('747','|cffffff00[|c1f40af20Announce by|r |cffff0000%s|cffffff00]:|r %s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('809','Account for character %s not found',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
('1000','Exiting daemon...',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
('1001','Account deleted: %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
('1002','Account %s NOT deleted (probably sql file format was updated)',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
('1003','Account %s NOT deleted (unknown error)',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
('1004','Account created: %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
('1005','Account name can\'t be longer than 16 characters (client limit), account not created!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1006,'Account with this name already exist!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1007,'Account %s NOT created (probably sql file format was updated)',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1008,'Account %s NOT created (unknown error)',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1009,'Player %s (Guid: %u) Account %s (Id: %u) deleted.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1010,'|    Account    |       Character      |       IP        | GM | TBC |',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1011,'|<Error>        | %20s |<Error>          |<Er>|<Err>|',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1100,'Account %s (Id: %u) have up to %u expansion allowed now.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1101,'Message of the day changed to:\r\n%s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1102,'Message sent to %s: %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1103,'%d - %s %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1104,'%d - %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1105,'%d - %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1106,'%d - %s %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1107,'%d - %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1108,'%d - %s %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1109,'%d - %s %s %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1110,'%d - %s X:%f Y:%f Z:%f MapId:%d',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1111,'%d - %s X:%f Y:%f Z:%f MapId:%d',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1112,'Failed to open file: %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1113,'Account %s (%u) have max amount allowed characters (client limit)',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1114,'Dump file has broken data!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1115,'Invalid character name!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1116,'Invalid character guid!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1117,'Character guid %u in use!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(1118,'%d - guild: %s (guid: %u) %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(5000,'You froze player %s.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(5001,'It might be amusing but no... you cant freeze yourself!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(5002,'Invalid input check the name of target.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(5003,'You unfroze player %s.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(5004,'There are no frozen players.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(5005,'Following players are frozen on the server:',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL),
(5006,'- %s',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);


-- cleanup command syntax
DELETE FROM command WHERE name IN (
  'gm ingame','gm online',
  'ban','ban account','ban character','ban ip',
  'baninfo','baninfo account','baninfo character','baninfo ip','pdump load',
  'banlist','banlist account','banlist character','banlist ip','help','transport',
  'unban','unban account','unban character','unban ip','list item','pdump write',
  'acct','account','account create','account delete','account onlinelist',
  'account set addon','account set gmlevel','account set password',
  'chardelete','gm list','gm online','sendmessage','server corpses','server exit','server motd',
  'server set loglevel','server set motd','security'

);

INSERT INTO command VALUES
('gm ingame',0,'Syntax: .gm ingame\r\n\r\nDisplay a list of available in game Game Masters.'),
('ban account',3,'Syntax is: ban account $Name $bantime $reason\r\nBan account kick player.\r\n$bantime: negative value leads to permban, otherwise use a timestring like \"4d20h3s\".'),
('ban character',3,'Syntax is: ban character $Name $bantime $reason\r\nBan account and kick player.\r\n$bantime: negative value leads to permban, otherwise use a timestring like \"4d20h3s\".'),
('ban ip',3,'Syntax is: ban ip $Ip $bantime $reason\r\nBan IP.\r\n$bantime: negative value leads to permban, otherwise use a timestring like \"4d20h3s\".'),
('baninfo account',3,'Syntax is: baninfo account\r\nWatch full information about a specific ban.'),
('baninfo character',3,'Syntax is: baninfo character\r\nWatch full information about a specific ban.'),
('baninfo ip',3,'Syntax is: baninfo ip\r\nWatch full information about a specific ban.'),
('banlist account',3,'Syntax is: banlist account [$Name]\r\nSearches the banlist for a account name pattern or show full list account bans.'),
('banlist character',3,'Syntax is: banlist character $Name\r\nSearches the banlist for a character name pattern. Pattern required.'),
('banlist ip',3,'Syntax is: banlist ip [$Ip]\r\nSearches the banlist for a IP pattern or show full list of IP bans.'),
('unban account',3,'Syntax is: unban account $Name\r\nUnban accounts for account name pattern.'),
('unban character',3,'Syntax is: unban character $Name\r\nUnban accounts for character name pattern.'),
('unban ip',3,'Syntax is: unban ip $Ip\r\nUnban accounts for IP pattern.'),
('pdump write',3,'Syntax is: pdump write $filename $playerNameOrGUID\r\nWrite character dump with name/guid $playerNameOrGUID to file $filename.'),
('pdump load',3,'Syntax is: pdump load $filename $account [$newname] [$newguid]\r\nLoad character dump from dump file into character list of $account with saved or $newname, with saved (or first free) or $newguid guid.'),
('list item',3,'Syntax: .list item #item_id [#max_count]\r\n\r\nOutput items with item id #item_id found in all character inventories, mails, auctions, and guild banks. Output item guids, item owner guid, owner account and owner name (guild name and guid in case guild bank). Will be output maximum #max_count items. If #max_count not provided use 10 as default value.'),
('help',0,'Syntax: .help [$command]\r\n\r\nDisplay usage instructions for the given $command. If no $command provided show list available commands.'),
('account',0,'Syntax: .account\r\n\r\nDisplay the access level of your account.'),
('account create',4,'Syntax: .account create $account $password\r\n\r\nCreate account and set password to it.'),
('account delete',4,'Syntax: .account delete $account\r\n\r\nDelete account with all characters.'),
('account onlinelist',4,'Syntax: .account onlinelist\r\n\r\nShow list of online accounts.'),
('account set addon',3,'Syntax: .account set addon [$account] #addon\r\n\r\nSet user (posible targeted) expansion addon level allowed. Addon values: 0 - normal, 1 - tbc, 2 - wotlk.'),
('account set gmlevel',4,'Syntax: .account set gmlevel [$account] #level\r\n\r\nSet the security level for targeted player (can''t be used at self) or for account $name to a level of #level.\r\n\r\n#level may range from 0 to 3.'),
('account set password',4,'Syntax: .account set password $account $password $password\r\n\r\nSet password for account.'),
('chardelete',4,'Syntax: .chardelete $charactername\r\n\r\nDelete character.'),
('gm list',3,'Syntax: .gm list\r\n\r\nDisplay a list of all Game Masters accounts and security levels.'),
('gm online',0,'Syntax: .gm online\r\n\r\nDisplay a list of available Game Masters.'),
('sendmessage',3,'Syntax: .sendmessage $playername $message\r\n\r\nSend screen message to player from ADMINISTRATOR.'),
('server corpses',2,'Syntax: .server corpses\r\n\r\nTriggering corpses expire check in world.'),
('server exit',4,'Syntax: .server exit\r\n\r\nTerminate Trinity NOW.'),
('server motd',0,'Syntax: .server motd\r\n\r\nShow server Message of the day.'),
('server set loglevel',4,'Syntax: .server set loglevel #level\r\n\r\nSet server log level (0 - errors only, 1 - basic, 2 - detail, 3 - debug).'),
('server set motd',3,'Syntax: .server set motd $MOTD\r\n\r\nSet server Message of the day.');