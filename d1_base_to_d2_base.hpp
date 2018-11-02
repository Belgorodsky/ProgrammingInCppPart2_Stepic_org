#pragma once
// base указывает на экземпляр Base, соответствующий D1
// нужно вернуть указатель на экземпляр Base, соответствующий D2
Base const * D1BaseToD2Base( Base const * base )
{
    return static_cast<D2 const *>(static_cast<D3 const *>(static_cast<D1 const *>(base)));
}
