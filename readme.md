# Open Knight Online (OpenKO)

<p align="left">
We started this project to learn more about how the MMORPG Knight Online works. MMORPGs are very intricate programs requiring knowledge in many areas of computer science such as TCP/IP, SQL server, performance tuning, 3D graphics and animation, load balancing, and more. Starting with the original leaked source we have updated to DirectX 9, wrapped window creation and player input using SDL 2.0, added function flags so that various file formats may be supported while remaining backwards compatible, and much much more.
</p>

<p align="left">
The goal of this project is to replicate official client functionality while preserving accuracy and compatibility with the official client.
We do not intend to introduce features not found in the official client, nor introduce custom behaviour in general. You're very welcome to do so in forks however, but these do not mesh with our design goals and introduce complexity and potentially incompatibility with the official client. Essentially, in the interests of accuracy, we'd like to keep the client's behaviour as close to official as possible, where it makes sense.

We may deviate in some minor aspects where it makes sense to fix, for example, UI behaviour, or to provide the user with error messages where the client may not officially do so, but these changes do not affect compatibility while improving the user experience.
Pull requests for such changes will be accepted on a case-by-case basis.
</p>

<p align="left">
This code is for academic purposes only! If you have questions, or would like help getting started, feel free visit the <a href="http://ko4life.net/topic/50-the-openko-project/" target="_blank">forums</a>.
</p>

#### Note:
* The UIE project currently requires VS15 pro

#### Intentional design decisions:
* _The project is currently focused around supporting the 1298/9 version of the game_. Version 1298/9 has most of the core functionality attributed to the game’s success. By ignoring later versions of the game we keep the system relatively simplistic. This allows us to strengthen the fundamental components of the game while minimizing the amount of reverse engineering necessary to make things work.
* _We stick to the 1298/9 database schema_. To ensure compatibility with the 1298/9 version of the game we do not modify the basic database schema. This means the structure of the database and how information is stored in the database doesn’t change while we are working. This could change once the core functionality of the 1298/9 is in place.

<br>

<p align="center">
	<img src="http://stephenmeier.net/files/openko_ex_00.png" />
</p>
